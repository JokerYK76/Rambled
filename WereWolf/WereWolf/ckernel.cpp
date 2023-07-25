#include "ckernel.h"
#include <QFileInfo>
#include <QSettings>
#include <QCoreApplication>
#include <QDebug>
#include <QByteArray>

CKernel::CKernel(QObject *parent) : QObject(parent), m_tx(0), m_id(0)
{

    m_loginDlg = new LoginDialog;
    m_mainDlg = new MainDialog;
    m_gameDlg = new GameRoomDialog;
    m_friendListDlg = new FriendList;
    m_createRoomDlg = NULL;
    m_addRoomDlg = NULL;
    m_roomListDlg = new RoomList;

    m_mainDlg->hide();
    m_gameDlg->hide();
    m_loginDlg->hide();
    m_friendListDlg->hide();
    m_roomListDlg->hide();

    m_pAudioRead = new Audio_Read;
    connect(m_pAudioRead, SIGNAL(sig_net_tx_frame(QByteArray)),
            this, SLOT(slot_sendAudioFrame(QByteArray)));
    connect(m_gameDlg, SIGNAL(SIG_openAudioDev()),
            m_pAudioRead, SLOT(ResumeAudio()));
    connect(m_gameDlg, SIGNAL(SIG_closeAudioDev()),
            m_pAudioRead, SLOT(PauseAudio()));


    //登陆界面槽函数绑定
    connect(m_loginDlg, SIGNAL(SIG_loginInfo(QString,QString)),
            this, SLOT(slot_loginInfo(QString,QString)));
    connect(m_loginDlg, SIGNAL(SIG_registerInfo(QString,QString,QString)),
            this, SLOT(slot_registerInfo(QString,QString,QString)));

    //主界面槽函数绑定
    connect(m_mainDlg, SIGNAL(SIG_clickFirendList()),
            this, SLOT(slot_clickFirendList()));
    connect(m_mainDlg, SIGNAL(SIG_createRoom()),
            this, SLOT(slot_createRoom()));
    connect(m_mainDlg, SIGNAL(SIG_addRoom()),
            this, SLOT(slot_addRoom()));
    connect(m_mainDlg, SIGNAL(SIG_getRoomList(int)),
            this, SLOT(slot_getRoomList(int)));
    connect(m_roomListDlg, SIGNAL(SIG_refreshRomList(int)),
            this, SLOT(slot_getRoomList(int)));

    //好友列表界面
    connect(m_friendListDlg, SIGNAL(SIG_searchOne(QString)),
            this, SLOT(slot_searchOne(QString)));

    //游戏房间界面
    connect(m_gameDlg, SIGNAL(SIG_leaveRoom(std::string,int)),
            this, SLOT(slot_leaveRoom(std::string,int)));
    connect(m_gameDlg, SIGNAL(SIG_sendRoomChatMsg(std::string,int,QString)),
            this, SLOT(slot_sendRoomChatMsg(std::string,int,QString)));
    connect(m_gameDlg, SIGNAL(SIG_readyGame(int,std::string)),
            this, SLOT(slot_readGame(int,std::string)));
    connect(m_gameDlg, SIGNAL(SIG_cancelReadyGame(int,std::string)),
            this, SLOT(slot_cancelReadGame(int,std::string)));
    //回合控制
    connect(m_gameDlg, SIGNAL(SIG_nightOver(int,int,int)),
            this, SLOT(slot_nightOver(int,int,int)));
    connect(m_gameDlg, SIGNAL(SIG_dayOver(int,int,int)),
            this, SLOT(slot_dayOver(int,int,int)));
    connect(m_gameDlg, SIGNAL(SIG_overRound(int,int)),
            this, SLOT(slot_overRound(int,int)));


    m_tcpClient = new TcpClientMediator;
    m_udpMediator = new UdpMediator;

    setNetMap();
    setConfig();

    m_tcpClient->OpenNet(m_ip.toStdString().c_str(), m_port);
    connect(m_tcpClient, SIGNAL(SIG_ReadyData(uint,char*,int)),
            this, SLOT(slot_dealReadyData(uint, char*,int)));

    m_udpMediator->OpenNet(m_ip.toStdString().c_str(), _DEFAULT_PORT_UDP);
    connect(m_udpMediator, SIGNAL(SIG_ReadyData(uint,char*,int)),
            this, SLOT(slot_dealReadyData(uint,char*,int)));

    m_loginDlg->show();

}

void CKernel::slot_createRoomInfo(int num, bool hasPwd, QString pwd)
{
    //打包 发送给服务器 返回roomID 8位
    STRU_CREATE_ROOM_RQ rq;
    rq.userID = m_id;
    rq.num = num;
    rq.hasPWD = hasPwd;
    rq.tx = m_tx;
    string strPwd = pwd.toStdString();
    strcpy(rq.pwd, strPwd.c_str());

    SendData((char*)&rq, sizeof(rq));
}

void CKernel::slot_addRoomInfo(QString roomID, QString pwd)
{
    qDebug() << __func__ ;
    m_roomListDlg->clear();
    m_roomListDlg->hide();
    STRU_ADD_ROOM_RQ rq;
    rq.tx = m_tx;
    string strPWD = pwd.toStdString();
    strcpy(rq.pwd, strPWD.c_str());
    string strID = roomID.toStdString();
    strcpy(rq.roomID, strID.c_str());
    rq.userID = m_id;

    SendData((char*)&rq, sizeof(rq));
}

void CKernel::SendData(char* buf, int len){
    m_tcpClient->SendData(0, buf, len);
}

//配置网络参数
void CKernel::setConfig()
{
    QString path = QCoreApplication::applicationDirPath()+"/config.ini";
    qDebug() << path;
    //可以考虑 有就读取，没有就写入默认值
    m_ip = _DEFAULT_IP;
    m_port = _DEFAULT_PORT;
    QFileInfo info(path);
    if(info.exists()){
        QSettings settings(path, QSettings::IniFormat, nullptr);
        settings.beginGroup("net");
        QVariant strip =  settings.value("ip");
        if(!strip.toString().isEmpty()) m_ip = strip.toString();
        QVariant nport = settings.value("port", 0);
        if(nport.toInt() != 0) m_port = nport.toInt();
        settings.endGroup();
    }else{
        QSettings settings(path, QSettings::IniFormat, nullptr);
        settings.beginGroup("net");
        settings.setValue("ip", m_ip);
        settings.setValue("port", m_port);
        settings.endGroup();
    }
    qDebug() << "ip:" << m_ip << " port:" << m_port;

}


//网络映射
#define NetMap(a) m_netMap[a - _DEF_PROTOCOL_BASE]
void CKernel::setNetMap()
{
    NetMap(_DEF_PACK_LOGIN_RS)      = &CKernel::slot_dealLoginRs;
    NetMap(_DEF_PACK_REGISTER_RS)   = &CKernel::slot_dealRegissterRs;
    NetMap(_DEF_PACK_FRIENDS_RS)    = &CKernel::slot_dealFriendInfoList;
    NetMap(_DEF_PACK_SEARCH_RS)     = &CKernel::slot_dealSearchRs;
    NetMap(_DEF_PACK_ADD_FRIEND_RQ) = &CKernel::slot_dealAddFriendRq;
    NetMap(_DEF_PACK_ADD_FRIEND_RS) = &CKernel::slot_dealAddFriendRs;
    NetMap(_DEF_PACK_CHAT)          = &CKernel::slot_dealChatPack;
    NetMap(_DEF_PACK_CREATE_ROOM_RS)= &CKernel::slot_dealCreateRoomRs;
    NetMap(_DEF_PACK_ADD_ROOM_RS)   = &CKernel::slot_dealAddRoomRs;
    NetMap(_DEF_PACK_LEAVE_ROOM_RS) = &CKernel::slot_dealLeaveRoomRs;
    NetMap(_DEF_PACK_ROOM_CHAT)     = &CKernel::slot_dealRoomChat;
    NetMap(_DEF_PACK_START)         = &CKernel::slot_dealStartGame;
    NetMap(_DEF_PACK_ROLE)          = &CKernel::slot_dealRole;
    NetMap(_DEF_PACK_ROUND)         = &CKernel::slot_dealRoundPack;
    NetMap(_DEF_PACK_ANSWER)        = &CKernel::slot_dealResult;
    NetMap(_DEF_PACK_AUDIO)         = &CKernel::slot_dealAudioFrame;
    NetMap(_DEF_PACK_IDENTITY)      = &CKernel::slot_dealIdentity;
    NetMap(_DEF_PACK_ROOMLIST_RS)   = &CKernel::slot_dealRoomListRs;
    NetMap(_DEF_PACK_ROOMCHAT)      = &CKernel::slot_dealRoomChatUdp;

}

void CKernel::slot_dealReadyData(uint lSendIP, char *buf, int len)
{
    char* tmp = buf;
    PackType packType = *(int*)tmp;
    if(packType < _DEF_PROTOCOL_BASE && packType > _DEF_PROTOCOL_BASE + _DEF_PROTOCOL_COUNT){
        return;
    }else{
        PFUN func = NetMap(packType);
        if(func)
            (this->*func)(lSendIP, buf, len);
    }
}
#include<QMessageBox>
void CKernel::slot_dealLoginRs(uint lSendIP, char *buf, int len)
{
    //拆包
    STRU_LOGIN_RS *rs = (STRU_LOGIN_RS*)buf;

    if(rs->result == login_success){
        QMessageBox::about(m_loginDlg, "提示", "登陆成功");

        //进入主界面
        m_name = rs->name;
        m_tx = rs->u_tx;
        m_id = rs->userid;
        m_mainDlg->setDlgInfo(m_name, m_id, rs->u_tx);
        m_loginDlg->hide();
        m_mainDlg->show();
//        m_gameDlg->setMyID(m_pos);

        //udp
        STRU_UDP_INFO info;
        info.userID = m_id;

        m_udpMediator->SendData( inet_addr(m_ip.toStdString().c_str()), (char*)&info, sizeof(info));
    }else if(rs->result == user_not_exist){
        QMessageBox::about(m_loginDlg, "提示", "用户不存在");
    }else{
        QMessageBox::about(m_loginDlg, "提示", "密码错误");
    }

}

void CKernel::slot_dealRegissterRs(uint lSendIP, char *buf, int len)
{
    //拆包
    STRU_REGISTER_RS *rs = (STRU_REGISTER_RS*)buf;

    if(rs->result == register_success){
        QMessageBox::about(m_loginDlg, "提示", "注册成功");
    }else if(rs->result == tel_is_exist){
        QMessageBox::about(m_loginDlg, "提示", "手机号存在");
    }else{
        QMessageBox::about(m_loginDlg, "提示", "昵称已存在");
    }
}

//处理返回好友列表
void CKernel::slot_dealFriendInfoList(uint lSendIP, char *buf, int len)
{
    qDebug() << __func__;
    m_friendListDlg->slot_clear();
    STRU_FRIENDINFO_LIST *pack = (STRU_FRIENDINFO_LIST*)buf;
    //逐个添加
    for(int i=0; i<pack->nums; ++i){
        FriendItem *item = new FriendItem;
        FriendInfo tmpInfo = pack->friends[i];
        item->slot_setInfo(tmpInfo.name, tmpInfo.userid, tmpInfo.label, tmpInfo.tx);
        connect(item, SIGNAL(SIG_addFriend(int)),
                this, SLOT(slot_addFriend(int)));
        connect(item, SIGNAL(SIG_chatWithOne(int,QString)),
                this, SLOT(slot_chatWithOne(int,QString)));
        m_friendListDlg->slot_addItem(item);
    }
    //添加完成 显示
    m_friendListDlg->show();
}

//处理搜索结果
void CKernel::slot_dealSearchRs(uint lSendIP, char *buf, int len)
{
    qDebug() << __func__;
    STRU_SEARCH_RS *rs = (STRU_SEARCH_RS*)buf;
    if(rs->relationship == _SEARCH_KIND_FRIEND){
        QMessageBox::about(m_friendListDlg, "提示", "已经是您的好友了");
        return;
    }else if(rs->relationship == _SEARCH_KIND_ISME){
        QMessageBox::about(m_friendListDlg, "提示", "请不要搜索自己哦");
        return;
    }else if(rs->relationship == _SEARCH_KIND_NO_EXIST){
        QMessageBox::about(m_friendListDlg, "提示", "用户不存在");
        return;
    }
    //界面显示搜索结果
    FriendItem *item = new FriendItem;
    item->slot_setInfo(rs->hisInfo.name, rs->hisInfo.userid, rs->hisInfo.label, rs->hisInfo.tx);
    connect(item, SIGNAL(SIG_addFriend(int)),
            this, SLOT(slot_addFriend(int)));
    connect(item, SIGNAL(SIG_chatWithOne(int,QString)),
            this, SLOT(slot_chatWithOne(int,QString)));
    item->show();
    //    m_friendListDlg->slot_showSearchResult(rs->hisInfo);
}

void CKernel::slot_dealAddFriendRq(uint lSendIP, char *buf, int len)
{
    qDebug() << __func__;
    //拆包
    STRU_ADD_FRIEND_RQ *rq = (STRU_ADD_FRIEND_RQ*)buf;
    //为什么显示在主界面呢？ 因为考虑后期添加为可以离线添加
    //这样登陆之后好友申请的返回包就会抵达
    int res = QMessageBox::question(m_mainDlg, "提示", QString("%1向您发送了好友申请").arg(rq->userID));
    STRU_ADD_FRIEND_RS rs;
    rs.userID = rq->userID;
    rs.hisID = rq->hisID;
    //通过点击结果返回申请结果
    if(res == QMessageBox::Yes){
        rs.result = _ADD_RESULT_AGREE;
    }else{
        rs.result = _ADD_RESULT_REFUSE;
    }
    SendData((char*)&rs, sizeof(rs));
}

void CKernel::slot_dealAddFriendRs(uint lSendIP, char *buf, int len)
{
    qDebug() << __func__;
    //拆包
    STRU_ADD_FRIEND_RS *rs = (STRU_ADD_FRIEND_RS*)buf;
    if(rs->result == _ADD_RESULT_AGREE){
        //为什么显示在主界面呢？ 因为考虑后期添加为可以离线添加
        //这样登陆之后好友申请的返回包就会抵达
        QMessageBox::about(m_mainDlg, "提示", QString("%1同意了您的好友申请").arg(rs->hisID));
        return;
    }else{
        QMessageBox::about(m_mainDlg, "提示", QString("%1拒绝了您的好友申请").arg(rs->hisID));
        return;
    }
}

void CKernel::slot_dealChatPack(uint lSendIP, char *buf, int len)
{
    //拆包
    STRU_CHAT *chatPack = (STRU_CHAT*)buf;
    slot_chatWithOne(chatPack->userID, chatPack->myName);
    //拿到窗口，显示
    ChatDlg *tmpDlg = m_mapIDtoChatDlg[chatPack->userID];
    tmpDlg->slot_addChatMsg(QString("%1").arg(chatPack->myName), QString("%1").arg(chatPack->content));
}

void CKernel::slot_dealCreateRoomRs(uint lSendIP, char *buf, int len)
{
    //拆包
    STRU_CREATE_ROOM_RS *rs = (STRU_CREATE_ROOM_RS*)buf;
    if(rs->result == _CREATE_ROOM_FAILED){
        //失败，提示
        QMessageBox::about(m_mainDlg, "提示", "创建房间失败");
        return;
    }
    m_mainDlg->hide();
    //成功, 创建 座位确定为1 不需要加到包里
    m_pos = 1;
    Audio_Write* item = new Audio_Write;
    m_mapIDtoAudioItem[1] = item;

    m_roomID = atoi(rs->roomID);
    m_gameDlg->setDlgInfo(rs->num, rs->roomID, m_tx, 1, rs->pwd);
    m_gameDlg->setMyID(m_pos);

}

void CKernel::slot_dealAddRoomRs(uint lSendIP, char *buf, int len)
{
    qDebug() <<__func__;
    //拆包
    STRU_ADD_ROOM_RS *rs = (STRU_ADD_ROOM_RS*)buf;
    if(rs->result == _ADD_ROOM_FAILED_NOROOM){
        //失败
        QMessageBox::about(m_mainDlg, "提示", "房间不存在");
        return;
    }else if(rs->result == _ADD_ROOM_FAILED_FULL){
        //失败
        QMessageBox::about(m_mainDlg, "提示", "房间已满");
        return;
    }else if(rs->result == _ADD_ROOM_FAILED_PWDERR){
        //失败
        QMessageBox::about(m_mainDlg, "提示", "密码错误");
        return;
    }
    m_roomID = atoi(rs->roomID);
    //成功 创建房间界面 入座

    if(m_mapIDtoAudioItem.find(rs->pos) == m_mapIDtoAudioItem.end()){
        Audio_Write* item = new Audio_Write;
        m_mapIDtoAudioItem[rs->pos] = item;
    }
    if(rs->userID == m_id){
        m_pos = rs->pos;
        m_gameDlg->setMyID(m_pos);
        m_gameDlg->setDlgInfo(rs->num, rs->roomID, rs->tx, rs->pos, rs->pwd);
    }else{
        m_gameDlg->setSeatImg(rs->pos, rs->tx);
    }
    m_mainDlg->hide();
}

void CKernel::slot_dealLeaveRoomRs(uint lSendIP, char *buf, int len)
{
    //拆包
    STRU_LEAVE_ROOM_RS *rs = (STRU_LEAVE_ROOM_RS*)buf;
    //控件删除
    if(m_mapIDtoAudioItem.find(rs->pos) != m_mapIDtoAudioItem.end()){
        Audio_Write *item = m_mapIDtoAudioItem[rs->pos];
        m_mapIDtoAudioItem.erase(rs->pos);
        delete item;
        item = NULL;
    }
    m_roomID = 0;
    m_gameDlg->delSeatImg(rs->pos);
}

void CKernel::slot_dealRoomListRs(uint lSendIP, char *buf, int len)
{
    qDebug() << __func__;
    STRU_ROOMLIST_RS *rs = (STRU_ROOMLIST_RS*)buf;
    qDebug() << rs->num ;
    for(int i=0; i<rs->num; ++i){
        RoomItem* item = new RoomItem;
        item->setInfo(rs->rooms[i].roomID, rs->rooms[i].hasPWD, rs->rooms[i].curNum, rs->rooms[i].maxNum);
        connect(item, SIGNAL(SIG_addRoom(QString,QString)),
                this, SLOT(slot_addRoomInfo(QString,QString)));
        m_roomListDlg->addRoomItem(item);
    }
    m_roomListDlg->show();
}

void CKernel::slot_dealRoomChat(uint lSendIP, char *buf, int len)
{
    STRU_ROOM_CHAT *pack = (STRU_ROOM_CHAT*)buf;
    m_gameDlg->slot_addChatMsg(QString("%1号").arg(pack->pos), QString(pack->content));
}

void CKernel::slot_dealStartGame(uint lSendIP, char *buf, int len)
{
    qDebug() << __func__ ;
    m_gameDlg->startGame();
}

void CKernel::slot_dealRole(uint lSendIP, char *buf, int len)
{
    STRU_ROLE *role = (STRU_ROLE*)buf;
    m_role = role->roleType;
    m_gameDlg->setRoleLabel(role->roleType);
}

void CKernel::slot_dealRoundPack(uint lSendIP, char *buf, int len)
{
    qDebug() << __func__ ;
    STRU_ROUND *pack = (STRU_ROUND*)buf;
    //显示回合
    isNight = pack->isNight;
    m_gameDlg->setRoundLabel(pack->roundNum, pack->isNight, pack->roleBehavior);
}

void CKernel::slot_dealResult(uint lSendIP, char *buf, int len)
{
    qDebug() << __func__;
    STRU_ANSWER *answer = (STRU_ANSWER*)buf;
    answer->who;
    answer->diedCause;
    //死亡通知
    m_gameDlg->setDiedInfo(answer->diedCause, answer->who, answer->second);
}

void CKernel::slot_dealIdentity(uint lSendIP, char *buf, int len)
{
    STRU_IDENTITY *rs = (STRU_IDENTITY*)buf;
    m_gameDlg->closeSeatPushButton(rs->id-1, 2);
    if(rs->identity == _ROLE_WOLF || rs->identity == _ROLE_WOLF_KING_WHITE)
        QMessageBox::about(m_gameDlg, "提示", QString("%1号, 狼").arg(rs->id));
    else
        QMessageBox::about(m_gameDlg, "提示", QString("%1号, 好人").arg(rs->id));
}

void CKernel::slot_dealGameOver(uint lSendIP, char *buf, int len)
{
    STRU_GAME_END *end = (STRU_GAME_END*)buf;
    m_gameDlg->clear();
    if(end->winCamp == _WIN_CAMP_GOOD){
        QMessageBox::about(m_gameDlg, "游戏结束", "好人胜利");
    }else{
        QMessageBox::about(m_gameDlg, "游戏结束", "狼人胜利");
    }
}

void CKernel::slot_dealAllWolf(uint lSendIP, char *buf, int len)
{
    STRU_ALLWOLF *pack = (STRU_ALLWOLF*)buf;
//    for(int i=0; i<pack->wolfNum; ++i){
//        m_gameDlg->closeSeatPushButton(pack->wolfs[i]);
    //    }
}

void CKernel::slot_dealRoomChatUdp(uint lSendIP, char *buf, int len)
{
    qDebug() << __func__ ;
    STRU_ROOMCHAT *rs = (STRU_ROOMCHAT*)buf;
    if(rs->myPos == m_pos){
        m_gameDlg->slot_addChatMsg("我", QString::fromStdString(rs->content));
    }else{
        m_gameDlg->slot_addChatMsg(QString("%1").arg(rs->myPos), QString::fromStdString(rs->content));
    }
}


//登录请求
void CKernel::slot_loginInfo(QString tel, QString pwd)
{
    STRU_LOGIN_RQ rq;
    string strPwd = pwd.toStdString();
    strcpy(rq.password, strPwd.c_str());
    string strTel = tel.toStdString();
    strcpy(rq.tel, strTel.c_str());

    SendData((char*)&rq, sizeof(rq));

}

//注册请求
void CKernel::slot_registerInfo(QString tel, QString pwd, QString name)
{
    STRU_REGISTER_RQ rq;
    string strPwd = pwd.toStdString();
    strcpy(rq.password, strPwd.c_str());
    string strTel = tel.toStdString();
    strcpy(rq.tel, strTel.c_str());
    string strName = name.toStdString();
    strcpy(rq.name, strName.c_str());

    SendData((char*)&rq, sizeof(rq));
}

void CKernel::slot_clickFirendList()
{
    qDebug() << __func__;
    //为什么点击后才获取，因为如果一开始获取那么后续更新，还需要再发，不如直接在这里发
    //发送包 获取好友列表信息
    STRU_FRIEND_RQ rq;
    rq.uid = m_id;
    SendData((char*)&rq, sizeof(rq));
}

void CKernel::slot_createRoom()
{
    if(m_createRoomDlg != NULL){
        delete m_createRoomDlg;
    }
    m_createRoomDlg = new CreateRoom;
    connect(m_createRoomDlg, SIGNAL(SIG_createRoomInfo(int,bool,QString)),
            this, SLOT(slot_createRoomInfo(int,bool,QString)));
    m_createRoomDlg->show();
}

void CKernel::slot_addRoom()
{
    if(m_addRoomDlg != NULL){
        delete m_addRoomDlg;
    }
    m_addRoomDlg = new AddRoom;
    connect(m_addRoomDlg, SIGNAL(SIG_addRoomInfo(QString,QString)),
            this, SLOT(slot_addRoomInfo(QString,QString)));
    m_addRoomDlg->show();
}

void CKernel::slot_getRoomList(int num)
{
    qDebug() << __func__;
    STRU_ROOMLIST_RQ rq;
    rq.roomType = num;
    //设置房间列表信息
    m_roomListDlg->setRoomNum(num);
    SendData((char*)&rq, sizeof(rq));
}


void CKernel::slot_searchOne(QString tel)
{
    qDebug() << __func__;
    STRU_SEARCH_RQ rq;
    rq.myID = m_id;
    strcpy(rq.tel, tel.toStdString().c_str());

    SendData((char*)&rq, sizeof(rq));
}

void CKernel::slot_addFriend(int userid)
{
    qDebug() << __func__ << "myID:" << m_id;
    //添加好友请求包
    STRU_ADD_FRIEND_RQ rq;
    rq.userID = m_id;
    rq.hisID = userid;

    SendData((char*)&rq, sizeof(rq));

}

void CKernel::slot_chatWithOne(int id, QString name)
{
    //查询是否已创建窗口
    ChatDlg *tmpDlg;
    if(m_mapIDtoChatDlg.count(id) > 0){
        //有，不需要创建，直接显示即可
        tmpDlg = m_mapIDtoChatDlg[id];
    }else{
        //创建聊天窗口
        tmpDlg = new ChatDlg;
        tmpDlg->slot_setInfo(id, name);
        connect(tmpDlg, SIGNAL(SIG_SendChatMsg(int,QString)),
                this, SLOT(slot_SendChatMsg(int,QString)));
        //添加到map
        m_mapIDtoChatDlg[id] = tmpDlg;
    }
    tmpDlg->show();
}
void CKernel::slot_SendChatMsg(int id, QString content)
{
    //聊天协议包
    STRU_CHAT chatPack;
    chatPack.userID = m_id;
    chatPack.hisID = id;
    string strContent = content.toStdString();
    strcpy(chatPack.content, strContent.c_str());
    string strName = m_name.toStdString();
    strcpy(chatPack.myName, strName.c_str());

    //发送
    SendData((char*)&chatPack, sizeof(chatPack));
}


void CKernel::slot_leaveRoom(std::string roomID, int pos)
{
    STRU_LEAVE_ROOM leavePack;
    strcpy(leavePack.roomID, roomID.c_str());
    leavePack.pos = pos;
    leavePack.userID = m_id;

    m_mapIDtoAudioItem.clear();

    SendData((char*)&leavePack, sizeof(leavePack));
    m_mainDlg->show();
}

void CKernel::slot_sendRoomChatMsg(std::string roomID, int pos, QString content)
{
//    //TCP
//    STRU_ROOM_CHAT pack;
//    strcpy(pack.roomID, roomID.c_str());
//    pack.pos = pos;
//    string strCon = content.toStdString();
//    strcpy(pack.content, strCon.c_str());

//    SendData((char*)&pack, sizeof(pack));
    //UDP
    qDebug() << __func__;
    string ip = m_ip.toStdString();
    qDebug() << m_ip;
    //分割四次 ip
    qDebug() << "ip:" <<inet_addr(ip.c_str());
//    unsigned int uIP = 0;
//    int beginPos = 0;
//    int endPos = 0;
//    string tmp;
//    for(int i=0; i<3; ++i){
//        endPos = ip.find(".", beginPos);
//        tmp = ip.substr(beginPos, endPos);
//        uIP += stoi(tmp);
//        uIP *= 256;
//        beginPos = endPos+1;
//    }
//    tmp = ip.substr(beginPos, ip.size());
//    uIP += stoi(tmp);
//    qDebug() << "ip:" << uIP;
    STRU_ROOMCHAT pack;
    pack.roomID = m_roomID;
    pack.myPos = m_pos;
    string str = content.toStdString();
    strcpy(pack.content, str.c_str());

    m_udpMediator->SendData( inet_addr(ip.c_str()), (char*)&pack, sizeof(pack));

}

void CKernel::slot_readGame(int pos, std::string roomID)
{
    //准备
    STRU_READY pack;
    pack.pos = pos;
    strcpy(pack.roomID, roomID.c_str());

    SendData((char*)&pack, sizeof(pack));
}

void CKernel::slot_cancelReadGame(int pos, string roomID)
{
    STRU_CANCEL_READY pack;
    pack.pos = pos;
    strcpy(pack.roomID, roomID.c_str());

    SendData((char*)&pack, sizeof(pack));
}


void CKernel::slot_nightOver(int roomID, int roleType, int id)
{
    qDebug() << __func__ ;
    STRU_BEHAVIOR rq;
    rq.roomID = roomID;
    rq.roleType = roleType;
    rq.who = id;

    SendData((char*)&rq, sizeof(rq));
}

void CKernel::slot_dayOver(int roomID, int roleType, int id)
{
    qDebug() << __func__ ;
    STRU_VOTEONE rq;
    rq.roomID = roomID;
    rq.myID = roleType;
    rq.hisID = id;

    SendData((char*)&rq, sizeof(rq));
}

void CKernel::slot_overRound(int roomID, int pos)
{
    STRU_OVER_ROUND rq;
    rq.myID = pos;
    rq.roomID = roomID;

    SendData((char*)&rq, sizeof(rq));
}

void CKernel::slot_sendAudioFrame(QByteArray data){
    int type = _DEF_PACK_AUDIO;
    int myPos = m_pos;
    int roomID = m_roomID;
    int role = _AUDIO_KIND_NORMAL;

    if(isNight && (m_role == _ROLE_WOLF || m_role == _ROLE_WOLF_KING_WHITE)){
        role = _AUDIO_KIND_WOLF;
    }

    char *buf = new char[16 + data.size()];
//    char *tmp = (char*)malloc(sizeof(int)*4 + data.size());
    char *tmp = buf;

    *(int*)tmp = type;
    tmp += sizeof(int);
    *(int*)tmp = myPos;
    tmp += sizeof(int);
    *(int*)tmp = roomID;
    tmp += sizeof(int);
    *(int*)tmp = role;
    tmp += sizeof(int);

    memcpy(tmp, data, data.size());

//    SendData(buf, 16 + data.size());
    m_udpMediator->SendData(inet_addr(m_ip.toStdString().c_str()), buf, 16 + data.size());
    delete[] buf;
}

void CKernel::slot_dealAudioFrame(uint lSendIP, char *buf, int len)
{
    qDebug() << __func__;
    char *tmp = buf;
    int type = *(int*)tmp;
    tmp += sizeof(int);
    int pos = *(int*)tmp;
    tmp += sizeof(int);
    int roomID = *(int*)tmp;
    tmp += sizeof(int);
    int role = *(int*)tmp;
    tmp += sizeof(int);

    if(pos == m_pos){
        return;
    }
    if(m_mapIDtoAudioItem.find(pos) != m_mapIDtoAudioItem.end()){
        QByteArray byte(tmp, len-16);
        Audio_Write *item = m_mapIDtoAudioItem[pos];
        item->slot_net_rx(byte);
    }

}
