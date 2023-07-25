#include "clogic.h"

void CLogic::setNetPackMap()
{
    NetPackMap(_DEF_PACK_REGISTER_RQ)   = &CLogic::RegisterRq;
    NetPackMap(_DEF_PACK_LOGIN_RQ)      = &CLogic::LoginRq;
    NetPackMap(_DEF_PACK_SEARCH_RQ)     = &CLogic::GetOneInfo;
    NetPackMap(_DEF_PACK_FRIENDS_RQ)    = &CLogic::GetFriendList;
    NetPackMap(_DEF_PACK_ADD_FRIEND_RQ) = &CLogic::AddFriendRq;
    NetPackMap(_DEF_PACK_ADD_FRIEND_RS) = &CLogic::AddFriendRs;
    NetPackMap(_DEF_PACK_CHAT)          = &CLogic::SendMsg;
    NetPackMap(_DEF_PACK_CREATE_ROOM_RQ)= &CLogic::CreateRoom;
    NetPackMap(_DEF_PACK_ADD_ROOM_RQ)   = &CLogic::AddRoom;
    NetPackMap(_DEF_PACK_LEAVE_ROOM)    = &CLogic::LeaveRoom;
    NetPackMap(_DEF_PACK_ROOM_CHAT)     = &CLogic::RoomChat;
    NetPackMap(_DEF_PACK_READY)         = &CLogic::ReadyGame;
    NetPackMap(_DEF_PACK_CANCEL_READY)  = &CLogic::CancelReadyGame;
    NetPackMap(_DEF_PACK_BEHAVIOR)      = &CLogic::RoleBehavior;
    NetPackMap(_DEF_PACK_VOTEONE)       = &CLogic::VoteBehavior;
    NetPackMap(_DEF_PACK_OVER_ROUND)    = &CLogic::OverSpeakRound;
    NetPackMap(_DEF_PACK_AUDIO)         = &CLogic::ForwardAudio;
    NetPackMap(_DEF_PACK_ROOMLIST_RQ)   = &CLogic::RoomListRq;

}
//注册
void CLogic::RegisterRq(sock_fd clientfd,char* szbuf,int nlen)
{
    printf("clientfd:%d RegisterRq\n", clientfd);
    //拆包
    STRU_REGISTER_RQ* rq = (STRU_REGISTER_RQ*)szbuf;

    //校验信息 tel pwd name
    list<string> res;//只需要校验有无即可
    char sqlBuf[1024] = "";
    sprintf(sqlBuf, "select u_tel from t_user where u_tel = '%s';", rq->tel);
    if(!m_sql->SelectMysql(sqlBuf, 1 , res)){
        printf("sql select error:%s\n",sqlBuf);
        return;
    }
    STRU_REGISTER_RS rs;
    if(!res.empty()){//存在 返回tel存在 结束
        rs.result = tel_is_exist;
    }else{
        res.clear();
        //名字是否存在
        sprintf(sqlBuf, "select u_name from t_user where u_tel = '%s';", rq->name);
        if(!m_sql->SelectMysql(sqlBuf, 1 , res)){
            printf("sql select error:%s\n",sqlBuf);
            return;
        }
        if(!res.empty()){//存在 返回name存在 结束
            STRU_REGISTER_RS rs;
            rs.result = name_is_exist;
        }else{
            //数据库添加信息
            sprintf(sqlBuf, "insert into t_user(u_tel,u_password,u_name, u_tx, u_label) values('%s','%s','%s', %d, '这个人很懒，没有留言');"
                    , rq->tel, rq->password, rq->name, 0);
            if(!m_sql->UpdataMysql(sqlBuf)){
                printf("sql updata error:%s\n",sqlBuf);
                return;
            }
            //返回结果
            rs.result = register_success;
        }
    }

    m_pKernel->SendData(clientfd, (char*)&rs, sizeof(rs));
}

//登录
void CLogic::LoginRq(sock_fd clientfd ,char* szbuf,int nlen)
{
    printf("clientfd:%d LoginRq\n", clientfd);
    //拆包
    STRU_LOGIN_RQ* rq = (STRU_LOGIN_RQ*)szbuf;
    //校验信息 tel pwd name
    list<string> res;//只需要校验有无即可
    char sqlBuf[1024] = "";
    STRU_LOGIN_RS rs;
    sprintf(sqlBuf, "select u_password, u_id, u_name, u_tx, u_label from t_user where u_tel = '%s';"
            , rq->tel);
    //sprintf(sqlBuf, "select u_tel from t_user where u_tel = '%s';", rq->tel);
    m_sql->SelectMysql(sqlBuf, 5 , res);
    if(res.size() == 0){//不存在 返回user不存在 结束
        rs.result = user_not_exist;
    }else{
        //存在 校验密码
        if(strcmp(res.front().c_str(), rq->password) != 0){//密码错误
            rs.result = password_error;
        }else{
            //更新map
            res.pop_front();
            int id = atoi(res.front().c_str());
            res.pop_front();
            std::string name = res.front();
            res.pop_front();
            int tx = atoi(res.front().c_str());
            res.pop_front();
            std::string label = res.front();
            res.pop_front();
            UserInfo* user;
            if(!m_mapIdToUserInfo.find(id, user)){
                user = new UserInfo;
            }else{//踢掉上一个登录

            }
            user->name = name;
            user->userid = id;
            user->clientfd = clientfd;
            //覆盖
            m_mapIdToUserInfo.insert(id, user);
            rs.result = login_success;
            strcpy(rs.name, name.c_str());
            rs.userid = id;
            rs.u_tx = tx;
            strcpy(rs.label, label.c_str());
        }
    }
    //返回结果
    m_pKernel->SendData(clientfd, (char*)&rs, sizeof(rs));

}

void CLogic::GetFriendList(sock_fd clientfd, char *szbuf, int nlen)
{
    printf("clientfd:%d GetFriendList\n", clientfd);
    //拆包
    STRU_FRIEND_RQ *rq = (STRU_FRIEND_RQ*)szbuf;
    //查询数据库
    list<string> res;
    char sqlBuf[1024] = "";
    //select * from t_user where u_id in (select u_hisid from t_friendship where u_myid = 1);
    sprintf(sqlBuf, "select u_id, u_name, u_tx, u_label from t_user where u_id in ("
                    "select u_hisid from t_friendship where u_myid = %d);", rq->uid);
    printf("sql:%s\n", sqlBuf);
    m_sql->SelectMysql(sqlBuf, 4, res);

    //好友列表包
    STRU_FRIENDINFO_LIST rs;
    rs.uid = rq->uid;
    int num = 0;
    while(res.size() != 0){
        FriendInfo tmpInfo;
        tmpInfo.userid = atoi(res.front().c_str());
        res.pop_front();
        strcpy(tmpInfo.name, res.front().c_str());
        res.pop_front();
        tmpInfo.tx = atoi(res.front().c_str());
        res.pop_front();
        strcpy(tmpInfo.label, res.front().c_str());
        res.pop_front();
        rs.friends[num++] = tmpInfo;
        //        printf("info: userid_%d, name_%s, tx_%d, label_%s\n",
        //               tmpInfo.userid, tmpInfo.name, tmpInfo.tx, tmpInfo.label);
    }
    rs.nums = num;
    printf("friends nums = %d\n", num);
    //发送
    SendData(clientfd, (char*)&rs, sizeof(rs));
}

void CLogic::GetOneInfo(sock_fd clientfd, char *szbuf, int nlen)
{
    printf("clientfd:%d GetOneInfo\n", clientfd);
    //拆包
    STRU_SEARCH_RQ *rq = (STRU_SEARCH_RQ*)szbuf;
    //查询数据库
    list<string> res;
    char sqlBuf[1024] = "";
    sprintf(sqlBuf, "select u_id, u_name, u_tx, u_label from t_user where u_tel = '%s';"
            , rq->tel);
    printf("sql:%s\n", sqlBuf);
    m_sql->SelectMysql(sqlBuf, 4, res);

    //返回包
    STRU_SEARCH_RS rs;

    if(res.size() != 0){
        FriendInfo tmpInfo;
        tmpInfo.userid = atoi(res.front().c_str());
        res.pop_front();
        strcpy(tmpInfo.name, res.front().c_str());
        res.pop_front();
        tmpInfo.tx = atoi(res.front().c_str());
        res.pop_front();
        strcpy(tmpInfo.label, res.front().c_str());
        res.pop_front();
        rs.hisInfo = tmpInfo;
        if(tmpInfo.userid == rq->myID){
            //是自己
            rs.relationship = _SEARCH_KIND_ISME;
        }
        //查询是否好友
        sprintf(sqlBuf, "select u_myid, u_hisid from t_friendship where u_id = %d and u_hisid = %d;", rq->myID, tmpInfo.userid);
        m_sql->SelectMysql(sqlBuf, 2, res);
        if(res.size() == 0){
            //非好友
            rs.relationship = _SEARCH_KIND_NOSHIP;
        }else{
            //是好友
            rs.relationship = _SEARCH_KIND_FRIEND;
        }

    }else{
        rs.relationship = _SEARCH_KIND_NO_EXIST;
    }
    //发送
    SendData(clientfd, (char*)&rs, sizeof(rs));
}

void CLogic::AddFriendRq(sock_fd clientfd, char *szbuf, int nlen)
{
    printf("clientfd:%d AddFriendRq\n", clientfd);
    //拆包
    STRU_ADD_FRIEND_RQ* rq = (STRU_ADD_FRIEND_RQ*)szbuf;
    printf("userID:%d , hisID:%d \n", rq->userID, rq->hisID);
    UserInfo* tmpInfo;
    if(m_mapIdToUserInfo.find(rq->hisID, tmpInfo) == true){
        //在线，转发请求
        SendData(tmpInfo->clientfd, szbuf, nlen);
        return;
    }else{
        //离线发送，待完成
        printf("对方不在线\n");
    }


}

void CLogic::AddFriendRs(sock_fd clientfd, char *szbuf, int nlen)
{
    printf("clientfd:%d AddFriendRs\n", clientfd);
    //拆包
    STRU_ADD_FRIEND_RS* rs = (STRU_ADD_FRIEND_RS*)szbuf;
    printf("userID:%d , hisID:%d \n", rs->userID, rs->hisID);

    UserInfo* tmpInfo;
    if(m_mapIdToUserInfo.find(rs->userID, tmpInfo) == true){
        if(rs->result == _ADD_RESULT_AGREE){
            //添加好友信息
            printf("添加好友信息\n");
            char sqlBuf[1024] = "";
            sprintf(sqlBuf, "insert into t_friendship(u_myid, u_hisid) values (%d, %d);",rs->userID, rs->hisID);
            printf("sql:%s\n", sqlBuf);
            m_sql->UpdataMysql(sqlBuf);
            sprintf(sqlBuf, "insert into t_friendship(u_myid, u_hisid) values (%d, %d);",rs->hisID, rs->userID);
            printf("sql:%s\n", sqlBuf);
            m_sql->UpdataMysql(sqlBuf);
        }
    }else{
        //离线发送，待完成
    }
    SendData(tmpInfo->clientfd, szbuf, nlen);
}

void CLogic::SendMsg(sock_fd clientfd, char *szbuf, int nlen)
{
    printf("clientfd:%d SendMsg\n", clientfd);
    //拆包
    STRU_CHAT *chat = (STRU_CHAT*)szbuf;
    UserInfo *tmpInfo;
    if(m_mapIdToUserInfo.find(chat->hisID, tmpInfo)){
        //找到了转发
        SendData(tmpInfo->clientfd, szbuf, nlen);
    }else{
        //离线
        printf("对方离线了\n");
    }
}

void CLogic::CreateRoom(sock_fd clientfd, char *szbuf, int len)
{
    printf("clientfd:%d CreateRoom\n", clientfd);
    //拆包
    STRU_CREATE_ROOM_RQ *rq = (STRU_CREATE_ROOM_RQ*)szbuf;
    //生成RoomID 8位 10000000~99999999
    int roomID = random()%90000000 + 10000000;
    while(m_mapRoomIDtoRoom.IsExist(roomID)){
        roomID = random()%90000000 + 10000000;
    }
    RoomInfo *tmpRoom = new RoomInfo;
    tmpRoom->maxNum = rq->num;
    tmpRoom->curNum = 1;
    memcpy(tmpRoom->pwd, rq->pwd, strlen(rq->pwd));
    tmpRoom->hasPwd = rq->hasPWD;
    if(strcmp(rq->pwd, "") == 0){
        tmpRoom->hasPwd = false;
    }
    tmpRoom->seatState[0] = rq->userID;
    tmpRoom->tx[0] = rq->tx;
    UserInfo *tmpInfo;
    m_mapIdToUserInfo.find(rq->userID, tmpInfo);
    tmpRoom->seatFd[0] = tmpInfo->clientfd;
    tmpRoom->seatIP[0] = tmpInfo->udpIP;
    tmpRoom->seatPort[0] = tmpInfo->udpPort;

    //添加到map
    m_mapRoomIDtoRoom.insert(roomID, tmpRoom);
    list<int> *tmpList;
    if(!m_roomList.find(rq->num, tmpList)){
        //没找到
        tmpList = new list<int>;
        m_roomList.insert(rq->num, tmpList);
    }
    tmpList->push_back(roomID);

    //回复
    STRU_CREATE_ROOM_RS rs;
    rs.num = rq->num;
    rs.result = _CREATE_ROOM_SUCCESS;
    string strRoomID = to_string(roomID);
    strcpy(rs.roomID, strRoomID.c_str());
    strcpy(rs.pwd, tmpRoom->pwd);
    rs.userID = rq->userID;

    SendData(clientfd, (char*)&rs, sizeof(rs));
}

//#define _ADD_ROOM_FAILED_NOROOM 1
//#define _ADD_ROOM_FAILED_FULL   2
//#define _ADD_ROOM_FAILED_PWDERR 3
void CLogic::AddRoom(sock_fd clientfd, char *szbuf, int len)
{

    //拆包
    STRU_ADD_ROOM_RQ *rq = (STRU_ADD_ROOM_RQ*)szbuf;
    RoomInfo *tmpRoomInfo;
    STRU_ADD_ROOM_RS rs;
    printf("clientfd:%d AddRoom roomID :%d\n", clientfd, atoi(rq->roomID));

    //    int id = atoi(rq->roomID);
    if(!m_mapRoomIDtoRoom.find(atoi(rq->roomID), tmpRoomInfo)){
        //没有房间
        rs.result = _ADD_ROOM_FAILED_NOROOM;
    }else{
        //有房间
        if(tmpRoomInfo->curNum == tmpRoomInfo->maxNum){
            //满了
            rs.result = _ADD_ROOM_FAILED_FULL;
        }else{
            //检查密码
            if(!tmpRoomInfo->hasPwd){
                //没密码直接加入
                rs.result = _ADD_ROOM_SUCCESS;
            }else{
                if(strcmp(rq->pwd, tmpRoomInfo->pwd) != 0){
                    //密码错误
                    rs.result = _ADD_ROOM_FAILED_PWDERR;
                }else{
                    //密码正确
                    rs.result = _ADD_ROOM_SUCCESS;
                }
            }
        }
    }

    if(rs.result == _ADD_ROOM_SUCCESS){
        //录入其他信息
        ++tmpRoomInfo->curNum;
        for(int i=0; i<tmpRoomInfo->maxNum; ++i){
            if(tmpRoomInfo->seatState[i] == 0){
                rs.pos = i+1;
                tmpRoomInfo->seatState[i] = rq->userID;
                UserInfo *tmpInfo;
                m_mapIdToUserInfo.find(rq->userID, tmpInfo);
                tmpRoomInfo->seatFd[i] = tmpInfo->clientfd;
                tmpRoomInfo->tx[i] = rq->tx;
                tmpRoomInfo->seatIP[i] = tmpInfo->udpIP;
                tmpRoomInfo->seatPort[i] = tmpInfo->udpPort;
                break;
            }
        }
        strcpy(rs.pwd, tmpRoomInfo->pwd);
        rs.num = tmpRoomInfo->maxNum;
        rs.userID = rq->userID;
        rs.tx = rq->tx;
        memcpy(rs.roomID, rq->roomID, strlen(rq->roomID));


        for(int i=0; i<tmpRoomInfo->maxNum; ++i){
            if(tmpRoomInfo->seatFd[i] != 0 && i != rs.pos-1){
                //向其他房间内成员也发送
                SendData(tmpRoomInfo->seatFd[i], (char*)&rs, sizeof(rs));
                //也要对其发送其他成员信息
                STRU_ADD_ROOM_RS backRs;
                backRs.tx = tmpRoomInfo->tx[i];
                backRs.num = tmpRoomInfo->maxNum;
                backRs.userID = tmpRoomInfo->seatState[i];
                backRs.pos = i+1;
                backRs.result = _ADD_ROOM_SUCCESS;
                memcpy(backRs.roomID, rq->roomID, strlen(rq->roomID));
                SendData(clientfd, (char*)&backRs, sizeof(backRs));
            }
        }
    }
    //发送回复
    SendData(clientfd, (char*)&rs, sizeof(rs));
}

void CLogic::LeaveRoom(sock_fd clientfd, char *szbuf, int len)
{
    printf("clientfd:%d LeaveRoom\n", clientfd);
    STRU_LEAVE_ROOM *pack = (STRU_LEAVE_ROOM*)szbuf;

    RoomInfo *tmpRoom;
    if(!m_mapRoomIDtoRoom.find(atoi(pack->roomID), tmpRoom)){
        return;
    }
    int i = pack->pos-1;

    //游戏结束
    tmpRoom->isStop = true;
    tmpRoom->isOver = true;

    tmpRoom->tx[i] = 0;
    --tmpRoom->curNum;
    tmpRoom->seatFd[i] = 0;
    tmpRoom->seatState[i] = 0;
    tmpRoom->seatIP[i] = "";
    tmpRoom->seatPort[i] = 0;

    if(tmpRoom->curNum == 0){
        printf("房间清空\n");

        //房间列表 list清除
        list<int>* tmpList;
        if(m_roomList.find(tmpRoom->maxNum, tmpList)){
            tmpList->remove(atoi(pack->roomID));
        }

        m_mapRoomIDtoRoom.erase(atoi(pack->roomID));
        delete tmpRoom;
        tmpRoom = NULL;
        return;
    }
    STRU_LEAVE_ROOM_RS rs;
    rs.pos = pack->pos;
    for(i=0; i<tmpRoom->maxNum; ++i){
        if(tmpRoom->seatFd[i] != 0){
            SendData(tmpRoom->seatFd[i], (char*)&rs, sizeof(rs));
        }
    }
}

void CLogic::RoomChat(sock_fd clientfd, char *szbuf, int len)
{
    printf("clientfd:%d RoomChat\n", clientfd);
    STRU_ROOM_CHAT *pack = (STRU_ROOM_CHAT*)szbuf;
    RoomInfo *tmpRoom;
    if(!m_mapRoomIDtoRoom.find(atoi(pack->roomID), tmpRoom)){
        return;
    }
    for(int i=0; i<tmpRoom->maxNum; ++i){
        if(pack->pos != i+1 && tmpRoom->seatFd[i] != 0){
            //转发房间消息
            SendData(tmpRoom->seatFd[i], (char*)pack, len);
        }
    }
}

void CLogic::ReadyGame(sock_fd clientfd, char *szbuf, int len)
{
    printf("clientfd:%d ReadyGame\n", clientfd);
    STRU_READY *pack = (STRU_READY*)szbuf;
    RoomInfo *tmpRoom;
    int id = atoi(pack->roomID);
    if(!m_mapRoomIDtoRoom.find(id, tmpRoom)){
        return;
    }
    if(tmpRoom->readyState[pack->pos] == 0){
        tmpRoom->readyState[pack->pos] = 1;
        ++tmpRoom->readyNum;
    }
    //测试 直接开始
    //    if(tmpRoom->readyNum == 2){
    //        STRU_START start;
    //        SendData(clientfd, (char*)&start, sizeof(start));
    //        ControlGame(tmpRoom);
    //    }

    //正常环节
    if(tmpRoom->readyNum == tmpRoom->maxNum){
        //游戏开始
        printf("游戏开始\n");
        STRU_START start;
        for(int i=0; i<tmpRoom->maxNum; ++i){
            //准备状态清空
            memset(tmpRoom->seatState, 0, sizeof(tmpRoom->seatState));
            if(tmpRoom->seatFd[i] != 0)
                SendData(tmpRoom->seatFd[i], (char*)&start, sizeof(start));
        }
        //游戏开始
        ControlGame(tmpRoom);
    }
}

void CLogic::CancelReadyGame(sock_fd clientfd, char *szbuf, int len)
{
    printf("clientfd:%d CancelReadyGame\n", clientfd);
    STRU_CANCEL_READY *pack = (STRU_CANCEL_READY*)szbuf;
    RoomInfo *tmpRoom;
    if(!m_mapRoomIDtoRoom.find(atoi(pack->roomID), tmpRoom)){
        return;
    }
    if(tmpRoom->readyState[pack->pos] == 1){
        tmpRoom->readyState[pack->pos] = 0;
        --tmpRoom->readyNum;
    }
}

void CLogic::RoleBehavior(sock_fd clientfd, char *szbuf, int len)
{

    STRU_BEHAVIOR *pack = (STRU_BEHAVIOR*)szbuf;
    if(pack->who == 0) return;
    printf("clientfd:%d RoleBehavior his roleType: %d\n", clientfd, pack->roleType);
    RoomInfo *room;
    if(!m_mapRoomIDtoRoom.find(pack->roomID, room)){
        return;
    }
    //狼杀
    if(pack->roleType == _ROLE_WOLF || pack->roleType == _ROLE_WOLF_KING_WHITE){
        printf("狼杀%d号\n", pack->who);
        ++room->seatVote[pack->who-1];
        if(room->seatVote[pack->who-1] > room->killCount){
            room->wolfKill = pack->who;
        }
    }
    //守护
    if(pack->roleType == _ROLE_GUARD){
        printf("守护%d号\n", pack->who);
        if(pack->who == room->lastGuard){
            return;
        }
        room->curGuard = pack->who;
    }
    //女巫
    if(pack->roleType == _BEHAVIOR_WITCH_SAVE){
        room->isDied = 1;
    }
    if(pack->roleType == _BEHAVIOR_WITCH_KILL){
        room->poisonKill = pack->who;
    }
    //预言家
    if(pack->roleType == _ROLE_PROPHET){
        if(room->hadProphet) return;
        room->hadProphet = true;
        printf("预言家检验%d号\n", pack->who);
        //将目标身份发给预言家
        STRU_IDENTITY rs;
        rs.identity = room->roleState[pack->who-1];
        rs.id = pack->who;
        SendData(clientfd, (char*)&rs, sizeof(rs));
    }
    //    //余下为投票环节
    //    if(pack->roleType == _BEHAVIOR_VOTE){
    //        ++room->seatVote[pack->who];
    //    }
}

void CLogic::VoteBehavior(sock_fd clientfd, char *szbuf, int len)
{
    //记票
    STRU_VOTEONE *vote = (STRU_VOTEONE*)szbuf;
    if(vote->hisID == 0) return;
    printf("clientfd:%d VoteBehavior his vote: %d\n", clientfd, vote->hisID);
    RoomInfo *room;
    if(!m_mapRoomIDtoRoom.find(vote->roomID, room)){
        return;
    }
    //记票+1
    if(vote->hisID == 0) return ;
    ++room->seatVote[vote->hisID-1];
}

void CLogic::OverSpeakRound(sock_fd clientfd, char *szbuf, int len)
{
    STRU_OVER_ROUND *over = (STRU_OVER_ROUND*)szbuf;
    RoomInfo *room;
    if(!m_mapRoomIDtoRoom.find(over->roomID, room)){
        return;
    }
    if(room->isOver == true)
        return;
    if(room->curRoundOne == over->myID)
        room->isStop = true;
}

void CLogic::ForwardAudio(sock_fd clientfd, char *szbuf, int len)
{
    printf("clientfd:%d ForwardAudio\n", clientfd);
    //取出数据
    char *data = szbuf;
    char *tmp = szbuf;
    int type = *(int*)tmp;
    tmp += sizeof(int);
    int pos = *(int*)tmp;
    tmp += sizeof(int);
    int roomID = *(int*)tmp;
    tmp += sizeof(int);
    int role = *(int*)tmp;
    tmp += sizeof(int);

    RoomInfo *room;
    if(!m_mapRoomIDtoRoom.find(roomID, room)){
        return;
    }
    if(role == _AUDIO_KIND_WOLF){
        //转发狼队友
        printf("转发给狼队友\n");
        for(int i=0; i<room->maxNum; ++i){
            if(pos != i-1 && room->roleState[i] == _ROLE_WOLF || room->roleState[i] == _ROLE_WOLF_KING_WHITE){
                SendData(room->seatFd[i], data, len);
            }
        }
    }else{
        //转发所有人
        printf("转发给所有人\n");
        for(int i=0; i<room->maxNum; ++i){
            if(pos != i-1){
                SendData(room->seatFd[i], data, len);
            }
        }
    }

}

void CLogic::RoomListRq(sock_fd clientfd, char *szbuf, int len)
{
    printf("clientfd:%d RoomListRq\n", clientfd);
    STRU_ROOMLIST_RQ *rq = (STRU_ROOMLIST_RQ*)szbuf;
    list<int> *tmpList;
    STRU_ROOMLIST_RS rs;
    RoomItemInfo info;
    if(m_roomList.find(rq->roomType, tmpList)){
        for(auto item : *tmpList){
            //逐个发送
            RoomInfo* tmpRoom;
            if(m_mapRoomIDtoRoom.find(item, tmpRoom)){
                info.curNum = tmpRoom->curNum;
                info.maxNum = tmpRoom->maxNum;
                info.hasPWD = tmpRoom->hasPwd;
                info.roomID = item;
                rs.rooms[rs.num++] = info;
            }
        }
    }
    SendData(clientfd, (char*)&rs, sizeof(rs));
}


void CLogic::ControlGame(RoomInfo *room)
{
    //分配身份
    AllocateRoles(room);
    room->isOver = false;
    //两秒后游戏开始
    sleep(2);
    printf("游戏开始\n");
    int roundNum = 0;
    STRU_ROUND pack;
    pack.roundNum = roundNum;

    while(1){
        //黑夜 角色行为环节
        pack.isNight = true;
        //狼人环节——同时为守卫环节
        pack.roleBehavior = _ROLE_WOLF;
        printf("狼人环节\n");
        SendToAll(room, pack);
        //沉睡
        sleep(_DEF_TIME_NIGHT+1);


        //女巫环节
        if(room->maxNum == 7){
            //告知死亡信息
            pack.whoDied = room->wolfKill;
            pack.roleBehavior = _ROLE_WITCH;
            SendToAll(room, pack);
            sleep(_DEF_TIME_NIGHT+1);
        }
        //预言家环节
        pack.roleBehavior = _ROLE_PROPHET;
        SendToAll(room, pack);
        //沉睡
        sleep(_DEF_TIME_NIGHT+1);
        //天亮了
        int diedOne = 0;
        if(room->wolfKill != 0){
            if(room->wolfKill == room->curGuard){
                if(room->isDied == 1){
                    //双奶 死
                    diedOne = room->wolfKill;
                }
            }else{
                if(room->isDied == 0){
                    //没救 死
                    diedOne = room->wolfKill;
                }
            }
        }
        //        if(room->poisonKill != 0){
        //            room->seatAlive[room->poisonKill-1] = 1;
        //            if(diedOne == 0){
        //                diedOne = room->poisonKill;
        //            }
        //        }
        //清空狼人投票
        room->hadProphet = false;
        memset(room->seatVote, 0, sizeof(room->seatVote));
        ++roundNum;
        STRU_ANSWER dieAnswer;
        dieAnswer.who = diedOne;
        dieAnswer.second = room->poisonKill;
        dieAnswer.diedCause = _ANSWER_KILL;
        SendToAll(room, dieAnswer);


        if(room->seatState[diedOne] == _ROLE_WOLF || room->seatState[diedOne] == _ROLE_WOLF_KING_WHITE){
            //狼
            --room->aliveWolfCount;
        }else if(room->seatState[diedOne] == _ROLE_CIVILIAN){
            //民
            --room->aliveCivilianCount;
        }else/* if (room->seatState[room->isDied] > _ROLE_CIVILIAN && room->seatState[room->isDied] < _ROLE_WOLF)*/{
            //神
            --room->aliveWolfCount;
        }

        if(room->seatState[room->poisonKill] == _ROLE_WOLF || room->seatState[room->poisonKill] == _ROLE_WOLF_KING_WHITE){
            //狼
            --room->aliveWolfCount;
        }else if(room->seatState[room->poisonKill] == _ROLE_CIVILIAN){
            //民
            --room->aliveCivilianCount;
        }else/*if(room->seatState[room->poisonKill] > _ROLE_CIVILIAN && room->seatState[room->poisonKill] < _ROLE_WOLF)*/{
            //神
            --room->aliveWolfCount;
        }
        //判断是否结束
        if(room->aliveGoldCount == 0 || room->aliveCivilianCount == 0){
            //狼获胜
            STRU_GAME_END endPack;
            endPack.winCamp = _WIN_CAMP_WOLF;
            SendToAll(room, endPack);
            for(int i=0; i<room->maxNum; ++i){
                //发送给所有人
                SendData(room->seatFd[i], (char*)&endPack, sizeof(endPack));
            }
        }
        if(room->aliveWolfCount == 0){
            //好人获胜
            STRU_GAME_END endPack;
            endPack.winCamp = _WIN_CAMP_GOOD;
            SendToAll(room, endPack);
            for(int i=0; i<room->maxNum; ++i){
                //发送给所有人
                SendData(room->seatFd[i], (char*)&endPack, sizeof(endPack));
            }
        }
        //发言环节 每个人60秒
        int randDir = rand()%2;
        int sayIDChange;
        if(randDir == 0){
            //顺时针
            sayIDChange = 1;
        }else{
            //逆时针
            sayIDChange = -1;
        }
        //循环形式计时 通过一个变量 来打破计时 点击结束发言
        int beginOne = rand()%room->maxNum+1;
        if(diedOne !=0 ){
            beginOne = diedOne;
        }
        for(int i = 0; i<room->maxNum; ++i){

            beginOne += sayIDChange + room->maxNum;
            beginOne %= room->maxNum;
            //死了就下一位
            if(room->seatAlive[beginOne] == 1) continue;
            //开始发言
            //向所有人 发送 此人发言环节
            if(beginOne == 0){
                beginOne = room->maxNum;
            }
            STRU_ROUND round;
            round.isNight = false;
            round.roundNum = roundNum;
            round.roleBehavior = beginOne;
            room->curRoundOne = beginOne;

            SendToAll(room, round);
            while(!room->isStop){
                usleep(50);
            }
            room->isStop = false;
            if(room->isOver){
                room->isOver = false;
                return ;
            }
        }
        //投票环节
        STRU_ROUND votePack;
        votePack.isNight = false;
        votePack.roundNum = roundNum;
        votePack.roleBehavior = _ROUND_VOTE;
        //发送所有人
        SendToAll(room, votePack);
        //结束标志 没有狼 或者没有民 或者没有 神
        sleep(_DEF_TIME_VOTE + 1);
        //记票
        int voteOne = 0;
        int voteNums = 0;
        for(int i=0; i<room->maxNum; ++i){
            if(room->seatVote[i] > voteNums){
                voteOne = i+1;
                voteNums = room->seatVote[i];
            }else if(room->seatVote[i] == voteNums){
                //平票不死
                voteOne = 0;
            }
            room->seatVote[i] = 0;
        }
        //发送投票结果
        STRU_ANSWER ans;
        ans.who = voteOne;
        ans.diedCause = _ANSWER_VOTE;
        room->seatAlive[voteOne] = 1;
        //发送所有人
        SendToAll(room, ans);

        //判断结束
        if(room->seatState[voteOne] == _ROLE_WOLF || room->seatState[voteOne] == _ROLE_WOLF_KING_WHITE){
            //狼
            --room->aliveWolfCount;
        }else if(room->seatState[voteOne] == _ROLE_CIVILIAN){
            //民
            --room->aliveCivilianCount;
        }else/*if(room->seatState[room->poisonKill] > _ROLE_CIVILIAN && room->seatState[room->poisonKill] < _ROLE_WOLF)*/{
            //神
            --room->aliveWolfCount;
        }
        //判断是否结束
        if(room->aliveGoldCount == 0 || room->aliveCivilianCount == 0){
            //狼获胜
            STRU_GAME_END endPack;
            endPack.winCamp = _WIN_CAMP_WOLF;
            SendToAll(room, endPack);
            for(int i=0; i<room->maxNum; ++i){
                //发送给所有人
                SendData(room->seatFd[i], (char*)&endPack, sizeof(endPack));
            }
        }
        if(room->aliveWolfCount == 0){
            //好人获胜
            STRU_GAME_END endPack;
            endPack.winCamp = _WIN_CAMP_GOOD;
            SendToAll(room, endPack);
            for(int i=0; i<room->maxNum; ++i){
                //发送给所有人
                SendData(room->seatFd[i], (char*)&endPack, sizeof(endPack));
            }
        }
        //放逐发言

        //恢复标志位
        room->poisonKill = 0;
        room->wolfKill = 0;
        room->killCount = 0;
        room->isDied = 0;
        room->lastGuard = room->curGuard;
        room->curGuard = 0;
        room->hadProphet = false;

    }

}

void CLogic::AllocateRoles(RoomInfo *room)
{
    printf("AllocateRoles\n");
    //可选项 人数 密码
    // 6——2狼 2平民 1预言家 1守卫
    // 7——1狼 1白狼王 1民 1预言家 1猎人 1守卫 1女巫
    // 9——3狼 3民 1预言家 1猎人 1女巫
    int wolfNum, civilianCount, prophetCount, witchCount, guardCount, whiteWolfCount, hunterCount;
    if(room->maxNum == 6){
        wolfNum = 2;
        civilianCount = 2;
        prophetCount = 1;
        witchCount = 0;
        guardCount = 1;
        whiteWolfCount = 0;
        hunterCount = 0;
    }else if(room->maxNum == 7){
        wolfNum = 1;
        civilianCount = 1;
        prophetCount = 1;
        witchCount = 1;
        guardCount = 1;
        whiteWolfCount = 1;
        hunterCount = 1;
    }else if(room->maxNum == 9){
        wolfNum = 3;
        civilianCount = 3;
        prophetCount = 1;
        witchCount = 1;
        guardCount = 0;
        whiteWolfCount = 0;
        hunterCount = 1;
    }
    int tmpNum = random()%room->maxNum;
    //分配狼人身份
    int *wolfs = (int*)malloc(sizeof(int)*wolfNum);
    STRU_ALLWOLF allWolf;
    allWolf.wolfNum = wolfNum;
    while(wolfNum){
        tmpNum = random()%room->maxNum;
        if(room->roleState[tmpNum] == 0){
            room->roleState[tmpNum] = _ROLE_WOLF;
            STRU_ROLE pack;
            pack.roleType = _ROLE_WOLF;
            SendData(room->seatFd[tmpNum], (char*)&pack, sizeof(pack));
            --wolfNum;
            wolfs[wolfNum] = tmpNum;
            ++room->aliveWolfCount;
        }
    }
    for(int i=0; i<allWolf.wolfNum; ++i){
        allWolf.wolfs[i] = wolfs[i];
    }
    for(int i=0; i<allWolf.wolfNum; ++i){
        SendData(room->seatFd[allWolf.wolfs[i]], (char*)&allWolf, sizeof(allWolf));
    }
    //分配平民身份
    while(civilianCount){
        tmpNum = random()%room->maxNum;
        if(room->roleState[tmpNum] == 0){
            room->roleState[tmpNum] = _ROLE_CIVILIAN;
            STRU_ROLE pack;
            pack.roleType = _ROLE_CIVILIAN;
            SendData(room->seatFd[tmpNum], (char*)&pack, sizeof(pack));
            --civilianCount;
            ++room->aliveCivilianCount;
        }
    }
    //分配预言家身份
    while(prophetCount){
        tmpNum = random()%room->maxNum;
        if(room->roleState[tmpNum] == 0){
            room->roleState[tmpNum] = _ROLE_PROPHET;
            STRU_ROLE pack;
            pack.roleType = _ROLE_PROPHET;
            SendData(room->seatFd[tmpNum], (char*)&pack, sizeof(pack));
            --prophetCount;
            ++room->aliveGoldCount;
        }
    }
    //分配守卫身份
    while(guardCount){
        tmpNum = random()%room->maxNum;
        if(room->roleState[tmpNum] == 0){
            room->roleState[tmpNum] = _ROLE_GUARD;
            STRU_ROLE pack;
            pack.roleType = _ROLE_GUARD;
            SendData(room->seatFd[tmpNum], (char*)&pack, sizeof(pack));
            --guardCount;
            ++room->aliveGoldCount;
        }
    }
    //分配女巫身份
    while(witchCount){
        tmpNum = random()%room->maxNum;
        if(room->roleState[tmpNum] == 0){
            room->roleState[tmpNum] = _ROLE_WITCH;
            STRU_ROLE pack;
            pack.roleType = _ROLE_WITCH;
            SendData(room->seatFd[tmpNum], (char*)&pack, sizeof(pack));
            --witchCount;
            ++room->aliveGoldCount;
        }
    }
    //分配猎人身份
    while(hunterCount){
        tmpNum = random()%room->maxNum;
        if(room->roleState[tmpNum] == 0){
            room->roleState[tmpNum] = _ROLE_HUNTER;
            STRU_ROLE pack;
            pack.roleType = _ROLE_HUNTER;
            SendData(room->seatFd[tmpNum], (char*)&pack, sizeof(pack));
            --hunterCount;
            ++room->aliveGoldCount;
        }
    }
    //分配白狼王身份
    while(whiteWolfCount){
        tmpNum = random()%room->maxNum;
        if(room->roleState[tmpNum] == 0){
            room->roleState[tmpNum] = _ROLE_WOLF_KING_WHITE;
            STRU_ROLE pack;
            pack.roleType = _ROLE_WOLF_KING_WHITE;
            SendData(room->seatFd[tmpNum], (char*)&pack, sizeof(pack));
            --whiteWolfCount;
            ++room->aliveWolfCount;
        }
    }
}

void CLogic::SendToAll(RoomInfo *room, STRU_ROUND pack)
{
    for(int i=0; i<room->maxNum; ++i){
        //发送给所有人
        SendData(room->seatFd[i], (char*)&pack, sizeof(pack));
    }
}

void CLogic::SendToAll(RoomInfo *room, STRU_ROLE pack)
{
    for(int i=0; i<room->maxNum; ++i){
        //发送给所有人
        SendData(room->seatFd[i], (char*)&pack, sizeof(pack));
    }
}

void CLogic::SendToAll(RoomInfo *room, STRU_ANSWER pack)
{
    for(int i=0; i<room->maxNum; ++i){
        //发送给所有人
        SendData(room->seatFd[i], (char*)&pack, sizeof(pack));
    }
}

void CLogic::SendToAll(RoomInfo *room, STRU_GAME_END pack)
{
    for(int i=0; i<room->maxNum; ++i){
        //发送给所有人
        SendData(room->seatFd[i], (char*)&pack, sizeof(pack));
    }
}

UdpSocket *CLogic::udpSock() const
{
    return m_udpSock;
}

MyMap<int, RoomInfo *> CLogic::mapRoomIDtoRoom() const
{
    return m_mapRoomIDtoRoom;
}





void * CLogic::UdpCustom(void *arg)
{
    CLogic* logic = (CLogic*)arg;
    UdpSocket* sock = logic->udpSock();
    RoomInfo *room;
    string buf;
    while(1)
    {
        string ip;
        uint16_t port;
        //接收数据
        buf.clear();
        sock->Recv(&buf, &ip, &port);
        char* tmpBuf = const_cast<char*>(buf.c_str());

        int type = *(int*)tmpBuf;
        if(type == _DEF_PACK_ROOMCHAT){
            //房间内群聊
            STRU_ROOMCHAT* pack = (STRU_ROOMCHAT*)tmpBuf;
            printf("roomID:%d\n", pack->roomID);
            if(logic->m_mapRoomIDtoRoom.find(pack->roomID, room)){
                //找到了就转发
                for(int i=0; i<room->maxNum; ++i){
                    if(/*pack->myPos != i+1 &&*/ room->seatFd[i] != 0){
                        //                        int clientFd = room->seatFd[i];
                        //                        struct sockaddr_in addr;
                        //                        socklen_t len = sizeof(addr);
                        //                        getsockname(clientFd, (struct sockaddr*)&addr, &len);
                        //                        string tmpIp = "192.168.1.36"/*inet_ntoa(addr.sin_addr)*/;
                        //                        cout << "client ip:" << tmpIp << "port:" << addr.sin_port <<endl;
                        sock->Send(tmpBuf, buf.length(), room->seatIP[i], room->seatPort[i]);
                    }
                }
            }
        }else if(type == _DEF_PACK_AUDIO){
            //语音 也是群聊
            printf("语音转发\n");
            char *data = tmpBuf;
            char *tmp = tmpBuf;
            int type = *(int*)tmp;
            tmp += sizeof(int);
            int pos = *(int*)tmp;
            tmp += sizeof(int);
            int roomID = *(int*)tmp;
            tmp += sizeof(int);
            int role = *(int*)tmp;
            tmp += sizeof(int);

            printf("roomID:%d\n", roomID);
            STRU_ROOMCHAT* pack = (STRU_ROOMCHAT*)tmpBuf;
//            if(!logic->m_mapRoomIDtoRoom.find(pack->roomID, room)){
//                continue;
//            }
            if(logic->m_mapRoomIDtoRoom.find(roomID, room))
            if(role == _AUDIO_KIND_WOLF){
                //转发狼队友
                printf("转发给狼队友\n");
                for(int i=0; i<room->maxNum; ++i){
                    if(pos != i-1 && room->roleState[i] == _ROLE_WOLF || room->roleState[i] == _ROLE_WOLF_KING_WHITE){
                        sock->Send(tmpBuf, buf.length(), room->seatIP[i], room->seatPort[i]);
                        //                            SendData(room->seatFd[i], data, len);
                    }
                }
            }else{
                //转发所有人
                printf("转发给所有人\n");
                for(int i=0; i<room->maxNum; ++i){
                    if(pos != i-1){
                        sock->Send(tmpBuf, buf.length(), room->seatIP[i], room->seatPort[i]);
                    }
                }
            }
        }else if(type == _DEF_PACK_UDP_INFO){
            STRU_UDP_INFO* pack = (STRU_UDP_INFO*)tmpBuf;
            UserInfo *tmpUser;
            if(logic->m_mapIdToUserInfo.find(pack->userID, tmpUser)){
                tmpUser->udpIP = ip;
                tmpUser->udpPort = port;
            }
        }

        //        cout << "server say: " << buf << endl;
    }
}
