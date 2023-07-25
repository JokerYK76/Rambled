#include "clogic.h"

void CLogic::setNetPackMap()
{
    NetPackMap(_DEF_PACK_REGISTER_RQ)    = &CLogic::RegisterRq;
    NetPackMap(_DEF_PACK_LOGIN_RQ)       = &CLogic::LoginRq;
    NetPackMap(_DEF_FILE_LIST_RQ)       = &CLogic::UserFileListRq;
    NetPackMap(_DEF_PACK_FILE_DOWNLOAD_RQ) = &CLogic::DownloadFileRq;
    NetPackMap(_DEF_PACK_FILE_HEAD_RS) = &CLogic::DownloadFileRs;
    NetPackMap(_DEF_PACK_FILE_CONTENT_RS) = &CLogic::FileContentRs;
    NetPackMap(_DEF_UPLOAD_FILE_RQ) = &CLogic::UploadFileRq;
    NetPackMap(_DEF_PACK_FILE_CONTENT_RQ) = &CLogic::FileContentRq;
    NetPackMap(_DEF_ADD_FOLDER_RQ) = &CLogic::AddFolderRq;
    NetPackMap(_DEF_PACK_DELETE_FILE_RQ) = &CLogic::DeleteFileRq;
    NetPackMap(_DEF_PACK_SHARE_FILE_RQ) = &CLogic::ShareFileRq;
    NetPackMap(_DEF_PACK_MY_SHARE_RQ) = &CLogic::MyShareRq;
    NetPackMap(_DEF_PACK_GET_SHARE_RQ) = &CLogic::GetShareRq;
    NetPackMap(_DEF_CONTINUE_DOWNLOAD_RQ) = &CLogic::ContinueDownload;
    NetPackMap(_DEF_GET_UPLOAD_POS_RQ) = &CLogic::GetUploadPosRq;

}

#define DEF_PATH "/home/lyk/colin/NetDisk/"
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
            sprintf(sqlBuf, "insert into t_user(u_tel,u_password,u_name) values('%s','%s','%s');"
                    , rq->tel, rq->password, rq->name);
            if(!m_sql->UpdataMysql(sqlBuf)){
                printf("sql updata error:%s\n",sqlBuf);
                return;
            }
            //存储信息 路径 /home/colin/NetDisk/user_id/
            sprintf(sqlBuf, "select u_id from t_user where u_tel = '%s';"
                    , rq->tel);
            res.clear();
            m_sql->SelectMysql(sqlBuf, 1 , res);
            int id = atoi( res.front().c_str() );
            char Path[260] = "";
            sprintf(Path, "%s%d/", DEF_PATH, id);
            umask(0);
            //mkdir(Path, S_IRWXU |S_IRWXO|S_IRWXG);//0777
            mkdir(Path, 0777);
            //S_IRWXU 拥有者   读写执行权限
            //S_IRWXG 组      读写执行权限
            //S_IRWXO 其他组   读写执行权限
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
    sprintf(sqlBuf, "select u_password, u_id, u_name from t_user where u_tel = '%s';"
            , rq->tel);
    //sprintf(sqlBuf, "select u_tel from t_user where u_tel = '%s';", rq->tel);
    m_sql->SelectMysql(sqlBuf, 3 , res);
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
        }
    }
    //返回结果
    m_pKernel->SendData(clientfd, (char*)&rs, sizeof(rs));

}

//文件列表请求
void CLogic::UserFileListRq(sock_fd clientfd, char *szbuf, int nlen)
{
    printf("Clientfd:%d, UserFileListRq;\n",clientfd);
    //拆包
    STRU_FILE_LIST_RQ* rq = (STRU_FILE_LIST_RQ*)szbuf;
    char sqlBuf[1024] = "";
    list<string> resultList;
    //通过用户id和路径->获取文件id
    sprintf(sqlBuf, "select * from t_file where f_id in (select f_id from t_user_file where u_id = %d and f_dir= '%s');"
            , rq->userid, rq->dir);
    if(!m_sql->SelectMysql(sqlBuf, 9, resultList)){
        printf("sql select error:%s\n",sqlBuf);
        return;
    }
    while(resultList.size() != 0){
        STRU_FILE_INFO info;
        info.userid = rq->userid;
        info.fileid = stoi(resultList.front());
        resultList.pop_front();
        strcpy(info.fileName, resultList.front().c_str());
        resultList.pop_front();
        strcpy(info.uploadTime, resultList.front().c_str());
        resultList.pop_front();
        info.size = stoi(resultList.front());
        resultList.pop_front();
        strcpy(info.dir, rq->dir);
        resultList.pop_front();
        resultList.pop_front();
        strcpy(info.md5, resultList.front().c_str());
        resultList.pop_front();
        resultList.pop_front();
        strcpy(info.fileType, resultList.front().c_str());
        resultList.pop_front();
        SendData(clientfd, (char*)&info, sizeof(info));
    }
}

//文件下载请求
void CLogic::DownloadFileRq(sock_fd clientfd, char *szbuf, int nlen)
{
    printf("Clientfd:%d, DownloadFileRq;\n",clientfd);
    //拆包
    STRU_DOWNLOAD_RQ* rq = (STRU_DOWNLOAD_RQ*)szbuf;
    //查数据库，获取信息
    char sqlBuf[1000] = "";
    sprintf(sqlBuf, "select t_file.f_id, f_name, f_type, f_md5, f_size, t_user_file.f_dir dir,f_path from t_file inner join t_user_file on t_file.f_id = t_user_file.f_id where t_user_file.u_id = %d and t_file.f_id = %d;", rq->userid, rq->fileid);
    list<string> lstRes;
    m_sql->SelectMysql( sqlBuf , 7 , lstRes );
    if(lstRes.size() == 0){
        //没有查询到 略
        cout << "select failed: " << sqlBuf << endl;
    }
    //建立文件下载映射 u_id f_id -> FileInfo
        FileInfo *info = new FileInfo;
        info->fileid = atoi(lstRes.front().c_str());lstRes.pop_front();
        info->name = lstRes.front();lstRes.pop_front();
        info->type = lstRes.front();lstRes.pop_front();
        info->md5 = lstRes.front();lstRes.pop_front();
        info->size = atoi(lstRes.front().c_str());lstRes.pop_front();
        info->dir = rq->dir;lstRes.pop_front();
        info->absolutePath = lstRes.front();lstRes.pop_front();

        info->filefd = open(info->absolutePath.c_str(), O_RDONLY);
        if(info->filefd <= 0){
            printf("file open failed %d\n", errno);
            return;
        }
    //文件处理
    if(info->type == "file"){
        //map映射
        char idBuf[100] = "";
        sprintf(idBuf, "%10d%10d", rq->userid, rq->fileid);
        string strId = idBuf;
        m_mapFileidtoFileInfo.insert(strId, info);
        //返回文件头请求
        STRU_FILE_HEAD_RQ headrq;
        strcpy( headrq.dir, info->dir.c_str());
        headrq.fileid = info->fileid;
        strcpy( headrq.fileName, info->name.c_str());
        strcpy( headrq.fileType, info->type.c_str());
        strcpy( headrq.md5, info->md5.c_str());
        headrq.size = info->size;

        SendData(clientfd, (char*)&headrq, sizeof(headrq));
    }else{
        //文件夹 todo
        DownLoadFolder(clientfd, rq->userid, info->fileid, info->name, info->dir);
        delete info;
    }
}
//文件头回复
void CLogic::DownloadFileRs(sock_fd clientfd, char *szbuf, int nlen)
{
    printf("Clientfd:%d, DownloadFileRs;\n",clientfd);
    STRU_FILE_HEAD_RS* rs = (STRU_FILE_HEAD_RS*)szbuf;
    FileInfo* info = nullptr;
    char idbuf[100] = "";
    sprintf(idbuf, "%10d%10d", rs->userid, rs->fileid);
    if( !m_mapFileidtoFileInfo.find(idbuf, info)){
        printf("file not found\n");
        return;
    }
    //发送文件内容
    STRU_FILE_CONTENT_RQ rq;
    rq.userid = rs->userid;
    rq.fileid = rs->fileid;
    rq.len = read(info->filefd, rq.content, _DEF_BUFFER);
    SendData(clientfd, (char*)&rq, sizeof(rq));
}
//文件内容回复
void CLogic::FileContentRs(sock_fd clientfd, char *szbuf, int nlen)
{
    printf("Clientfd:%d, FileContentRs;\n",clientfd);
    STRU_FILE_CONTENT_RS* rs = (STRU_FILE_CONTENT_RS*)szbuf;
    //返回结果
    FileInfo* info = nullptr;
    char idbuf[100] = "";
    sprintf(idbuf, "%10d%10d", rs->userid, rs->fileid);
    if( !m_mapFileidtoFileInfo.find(idbuf, info)){
        printf("file not found\n");
        return;
    }
    //不成功 重新发送
    if(rs->result == 0){
        lseek(info->filefd, -1*rs->len, SEEK_CUR);
    }
    //成功 移动pos
    info->pos += rs->len;
    //判断是否读完
    if(info->pos >= info->size){
        //读完
        close(info->filefd);
        m_mapFileidtoFileInfo.erase(idbuf);
        delete info;
        return;
    }
    //发送文件内容
    STRU_FILE_CONTENT_RQ rq;
    rq.userid = rs->userid;
    rq.fileid = rs->fileid;
    rq.len = read(info->filefd, rq.content, _DEF_BUFFER);
    SendData(clientfd, (char*)&rq, sizeof(rq));
}
//文件上传请求
void CLogic::UploadFileRq(sock_fd clientfd, char *szbuf, int nlen)
{
    printf("Clientfd:%d, UploadFileRq;\n",clientfd);
    //拆包 获取信息
    STRU_UPLOAD_FILE_RQ *rq = (STRU_UPLOAD_FILE_RQ*) szbuf;
    //查看MD5和filename以及state（是否上传完毕） 看是否能秒传
    char sqlBuf[1000] = "";
    list<string> lstRes;
    sprintf(sqlBuf, "select f_id from t_file where f_name = '%s' and\
                    f_MD5 = '%s' and f_state = 1;", rq->fileName, rq->md5);
    m_sql->SelectMysql(sqlBuf, 1, lstRes);
    if(lstRes.size() > 0){
        //秒传
        printf("Clientfd:%d, STRU_QUICK_UPLOAD_RS;\n",clientfd);
        int fileid = stoi(lstRes.front());
        sprintf(sqlBuf, "insert into t_user_file values(%d, %d, '%s');",
                rq->userid, fileid, rq->dir);
        if(!m_sql->UpdataMysql(sqlBuf)){
            printf("sql Error:%s\n", sqlBuf);
        }
//        sprintf(sqlBuf, "update t_file set f_count = f_count + 1 where f_id = %d;",
//                fileid);
//        if(!m_sql->UpdataMysql(sqlBuf)){
//            printf("sql Error:%s\n", sqlBuf);
//        }
        STRU_QUICK_UPLOAD_RS rs;
        strcpy(rs.md5, rq->md5);
        rs.fileid = fileid;
        rs.userid = rq->userid;
        SendData(clientfd, (char*)&rs, sizeof(rs));
        return;
    }
    //不是秒传
    //创建信息结构体
    FileInfo *info = new FileInfo;
    char pathBuf[1000] = "";
    //NetDisk路径 + userid + 文件路径
    sprintf(pathBuf, "%s%d%s%s", DEF_PATH, rq->userid, rq->dir, rq->fileName);
    info->absolutePath = pathBuf;
    info->dir = rq->dir;
    info->md5 = rq->md5;
    //info->fileid;
    info->name = rq->fileName;
    info->time =  rq->time;
    info->type = rq->fileType;
    info->size = rq->size;
    //数据库插入信息 文件信息表

    sprintf(sqlBuf, "insert into t_file (f_name ,  f_uploadtime ,  f_size ,  f_path ,  f_count ,  f_MD5  , f_state , f_type ) \
            values ( '%s' , '%s' , %d , '%s' , 0, '%s' , 0  , '%s' );",
            rq->fileName, rq->time, rq->size, pathBuf, rq->md5, rq->fileType);
    if(!m_sql->UpdataMysql(sqlBuf)){
        cout<< "sql UpdataMysql Failed:" << sqlBuf <<endl;
        return;
    }
    //查询数据库，获取fielid
    sprintf(sqlBuf, "select f_id from t_file where f_name = '%s' and f_MD5 = '%s'", rq->fileName, rq->md5);
    bool res = m_sql->SelectMysql(sqlBuf, 1, lstRes);
    if(!res){
        cout<< "sql SelectMysql Failed:" << sqlBuf <<endl;
        return;
    }
    info->fileid = stoi(lstRes.front());
    lstRes.pop_front();
    //数据库插入信息 用户文件关系表  insert into t_user_file ( u_id , f_id , f_dir ) values( 3 , 1, '/');
    sprintf(sqlBuf,"insert into t_user_file ( u_id , f_id , f_dir ) values( %d , %d, '%s');",
            rq->userid, info->fileid, rq->dir);
    if(!m_sql->UpdataMysql(sqlBuf)){
        cout<< "sql UpdataMysql Failed:" << sqlBuf <<endl;
        return;
    }
    //打开文件
    info->filefd = open(pathBuf, O_CREAT | O_WRONLY | O_TRUNC, 0777);//权限 八进制
    if(info->fileid <= 0){
        cout<< "open file faled" <<endl;
        return;
    }
    //添加map
    char strid[100] = "";
    sprintf(strid, "%10d%10d", rq->userid, info->fileid);
    m_mapFileidtoFileInfo.insert(strid, info);
    //回复
    STRU_UPLOAD_FILE_RS rs;
    strcpy(rs.md5, info->md5.c_str());
    rs.fileid = info->fileid;
    rs.userid = rq->userid;
    rs.result = 1;//默认成功
    SendData(clientfd, (char*)&rs, sizeof(rs));
}
//文件内容上传请求
void CLogic::FileContentRq(sock_fd clientfd, char *szbuf, int nlen)
{
    printf("Clientfd:%d, FileContentRq;\n",clientfd);
    //拆包
    STRU_FILE_CONTENT_RQ *rq = (STRU_FILE_CONTENT_RQ*)szbuf;
    //map获取FileInfo 写入
    char idbuf[100] = "";
    sprintf(idbuf, "%10d%10d", rq->userid, rq->fileid);
    FileInfo *info = nullptr;
    if(!m_mapFileidtoFileInfo.find(idbuf,info)){
        cout<< "fileinfo not found" << endl;
        return;
    }
    int len = write(info->filefd, rq->content, rq->len);
    //判断写入结果
    STRU_FILE_CONTENT_RS rs;
    if(len != rq->len){
        //失败
        lseek(info->filefd, -1*len, SEEK_CUR);
        rs.result = 0;
    }else{
        //成功
        rs.result = 1;
        info->pos += len;
        //写完 关闭fd 更新数据库state
        if(info->pos >= info->size){
            close(info->filefd);
            m_mapFileidtoFileInfo.erase(idbuf);
            delete info;
            char sqlBuf[1000] = "";
            sprintf(sqlBuf, "update t_file set f_state = 1 where f_id = %d;",
                    rq->fileid);
            m_sql->UpdataMysql(sqlBuf);
        }
    }
    rs.len = rq->len;
    rs.fileid = rq->fileid;
    rs.userid = rq->userid;
    SendData(clientfd, (char*)&rs, sizeof(rs));
}

void CLogic::AddFolderRq(sock_fd clientfd, char *szbuf, int nlen)
{
    printf("Clientfd:%d, AddFolderRq;\n",clientfd);
    //拆包 获取信息
    STRU_ADD_FOLDER_RQ *rq = (STRU_ADD_FOLDER_RQ*) szbuf;
    //查看MD5和filename以及state（是否上传完毕） 看是否能秒传
    char sqlBuf[1000] = "";
    list<string> lstRes;
    sprintf(sqlBuf, "select f_id from t_file where f_name = '%s' and\
                    f_MD5 = '%s' and f_state = 1;", rq->fileName, rq->md5);
    m_sql->SelectMysql(sqlBuf, 1, lstRes);
    if(lstRes.size() > 0){
        //秒传
        printf("Clientfd:%d, STRU_QUICK_UPLOAD_RS;\n",clientfd);
        int fileid = stoi(lstRes.front());
        sprintf(sqlBuf, "insert into t_user_file values(%d, %d, '%s');",
                rq->userid, fileid, rq->dir);
        if(!m_sql->UpdataMysql(sqlBuf)){
            printf("sql Error:%s\n", sqlBuf);
        }
//        sprintf(sqlBuf, "update t_file set f_count = f_count + 1 where f_id = %d;",
//                fileid);
//        if(!m_sql->UpdataMysql(sqlBuf)){
//            printf("sql Error:%s\n", sqlBuf);
//        }
        STRU_QUICK_UPLOAD_RS rs;
        strcpy(rs.md5, rq->md5);
        rs.fileid = fileid;
        rs.userid = rq->userid;
        SendData(clientfd, (char*)&rs, sizeof(rs));
        return;
    }
    //不是秒传
    char pathBuf[1000] = "";
    //NetDisk路径 + userid + 文件路径
    sprintf(pathBuf, "%s%d%s%s", DEF_PATH, rq->userid, rq->dir, rq->fileName);
    //数据库插入信息 文件信息表
    int fileid = 0;
    sprintf(sqlBuf, "select f_id from t_file where f_name = '%s' and f_type = '%s'",
            rq->fileName, "dir");
    bool res = m_sql->SelectMysql(sqlBuf, 1, lstRes);
    if(!res){
        cout<< "sql SelectMysql Failed:" << sqlBuf <<endl;
        return;
    }
    if(lstRes.size() == 0){
        sprintf(sqlBuf, "insert into t_file (f_name ,  f_uploadtime ,  f_size ,  f_path ,  f_count ,  f_MD5  , f_state , f_type ) \
                values ( '%s' , '%s' , %d , '%s' , 1, '%s' , 1  , '%s' );",
                rq->fileName, rq->time, rq->size, pathBuf, rq->md5, rq->fileType);
        if(!m_sql->UpdataMysql(sqlBuf)){
            cout<< "sql UpdataMysql Failed:" << sqlBuf <<endl;
            return;
        }
        //查询数据库，获取fielid
        sprintf(sqlBuf, "select f_id from t_file where f_name = '%s' and f_MD5 = '%s'", rq->fileName, rq->md5);
        bool res = m_sql->SelectMysql(sqlBuf, 1, lstRes);
        if(!res){
            cout<< "sql SelectMysql Failed:" << sqlBuf <<endl;
            return;
        }
        fileid = stoi(lstRes.front());
        lstRes.pop_front();
    }else{
        fileid = stoi(lstRes.front());
        lstRes.pop_front();
    }
    //数据库插入信息 用户文件关系表  insert into t_user_file ( u_id , f_id , f_dir ) values( 3 , 1, '/');
    sprintf(sqlBuf,"insert into t_user_file ( u_id , f_id , f_dir ) values( %d , %d, '%s');",
            rq->userid, fileid, rq->dir);
    if(!m_sql->UpdataMysql(sqlBuf)){
        cout<< "sql UpdataMysql Failed:" << sqlBuf <<endl;
        return;
    }
    //创建文件夹
    umask(0);
    mkdir(pathBuf, 0777);

    //回复
    STRU_ADD_FOLDER_RS rs;
    rs.result = 1;//默认成功
    SendData(clientfd, (char*)&rs, sizeof(rs));
}

void CLogic::DeleteFileRq(sock_fd clientfd, char *szbuf, int nlen)
{
    printf("Clientfd:%d, DeleteFileRq;\n",clientfd);
    STRU_DELETE_FILE_RQ* rq = (STRU_DELETE_FILE_RQ*)szbuf;
    int count = rq->fileCount;
    for(int i=0; i<count; ++i){
        DeleteItem(rq->userid, rq->fileidArray[i], rq->dir);
    }
    STRU_DELETE_FILE_RS rs;
    strcpy(rs.dir, rq->dir);
    rs.result = 1;
    SendData(clientfd, (char*)&rs, sizeof(rs));
}

void CLogic::ShareFileRq(sock_fd clientfd, char *szbuf, int nlen)
{
    printf("Clientfd:%d, ShareFileRq;\n",clientfd);
    STRU_SHARE_FILE_RQ* rq = (STRU_SHARE_FILE_RQ*)szbuf;
    //生成分享码link
    int link = 0;
    do {
        link = random() % 9 + 1;
        link *= 10000000;
        link += random() % 10000000;
        char sqlBuf[1000] = "";
        list<string> lstRes;
        sprintf(sqlBuf, "select s_link from t_shareFile where s_link = %d;",
                link);
        m_sql->SelectMysql(sqlBuf, 1, lstRes);
        if(lstRes.size() != 0){
            link = 0;
        }
    } while (link == 0);
    int n = rq->itemCount;
    for(int i=0; i<n; ++i){
        //调用分享处理函数
        ShareItem( rq->userid, rq->fileidArray[i], rq->dir, rq->shareTime, link);
    }
    //回复
    STRU_SHARE_FILE_RS rs;
    rs.result = 1;
    SendData(clientfd, (char*)&rs, sizeof(rs));
}

void CLogic::MyShareRq(sock_fd clientfd, char *szbuf, int nlen)
{
    printf("Clientfd:%d, MyShareRq;\n",clientfd);
    STRU_MY_SHARE_RQ* rq = (STRU_MY_SHARE_RQ*)szbuf;
    char sqlBuf[1000] = "";
    list<string> lstRes;
    sprintf(sqlBuf, "select f_name, f_size, s_linkTime, s_link from share_file_info where u_id = %d;", rq->userid);
    m_sql->SelectMysql(sqlBuf, 4, lstRes);
    if(lstRes.size() == 0) return;
    int len = sizeof(STRU_MY_SHARE_RS) + sizeof(MY_SHARE_FILE)*(lstRes.size()/4);
    STRU_MY_SHARE_RS* rs = (STRU_MY_SHARE_RS*)malloc(len);
    rs->init();
    rs->itemCount = lstRes.size()/4;
    int count = 0;
    while(lstRes.size() != 0){
        string strName = lstRes.front();
        strcpy( rs->items[count].name, strName.c_str() );
        lstRes.pop_front();
        rs->items[count].size = stoi(lstRes.front());
        lstRes.pop_front();
        string strTime = lstRes.front();
        strcpy( rs->items[count].time, strTime.c_str() );
        lstRes.pop_front();
        rs->items[count].shareLink = stoi(lstRes.front());
        lstRes.pop_front();
        ++count;
    }
    //回复
    SendData(clientfd, (char*)rs, len);
}

void CLogic::GetShareRq(sock_fd clientfd, char *szbuf, int nlen)
{
    printf("Clientfd:%d, GetShareRq;\n",clientfd);
    STRU_GET_SHARE_RQ* rq = (STRU_GET_SHARE_RQ*)szbuf;
    //查数据库 找到分享的文件 类型 文件id
    char sqlBuf[1000] = "";
    sprintf(sqlBuf, "select u_id, f_id, f_dir, f_type, f_name from share_file_info where s_link = %d;", rq->shareLink);
    list<string> lstRes;
    bool res = m_sql->SelectMysql(sqlBuf, 5, lstRes);
    if(!res){
        cout<< "select failed: " << sqlBuf << endl;
        return;
    }
    while(lstRes.size() != 0){
        int fromUserId = stoi(lstRes.front()); lstRes.pop_front();
        int fileId = stoi(lstRes.front()); lstRes.pop_front();
        string dir = lstRes.front(); lstRes.pop_front();
        string type = lstRes.front(); lstRes.pop_front();
        string name = lstRes.front(); lstRes.pop_front();

        //不应该分类处理， 都是只加入一次表
        GetShareByFile(rq->userid, fileId, dir);
        //根据文件类型 处理
//        if(type == "file"){
//            GetShareByFile(rq->userid, fileId, dir);
//        }else{
//            GetShareByFolder(rq->userid, fileId, rq->dir, fromUserId, dir, name);
//        }
    }
    STRU_GET_SHARE_RS rs;
    strcpy(rs.dir , rq->dir);
    rs.result = 1;
    SendData(clientfd, (char*)&rs, sizeof(rs));
}

void CLogic::ContinueDownload(sock_fd clientfd, char *szbuf, int nlen)
{
    //拆包
    STRU_CONTINUE_DOWNLOAD_RQ * rq = (STRU_CONTINUE_DOWNLOAD_RQ*) szbuf;

    FileInfo *info = nullptr;
    char idBuf[1000] = "";
    sprintf(idBuf, "%10d%10d", rq->userid, rq->fileid);

    if( !m_mapFileidtoFileInfo.find(idBuf, info) ){
        //服务器map未存储文件信息，查表添加文件信息
        //查数据库，获取信息
        char sqlBuf[1000] = "";
        sprintf(sqlBuf, "select t_file.f_id, f_name, f_type, f_md5, f_size, t_user_file.f_dir dir,f_path from t_file inner join t_user_file on t_file.f_id = t_user_file.f_id where t_user_file.u_id = %d and t_file.f_id = %d;", rq->userid, rq->fileid);
        list<string> lstRes;
        m_sql->SelectMysql( sqlBuf , 7 , lstRes );
        if(lstRes.size() == 0){
            //没有查询到 略
            cout << "select failed: " << sqlBuf << endl;
        }
        //建立文件下载映射 u_id f_id -> FileInfo
            info = new FileInfo;
            info->fileid = atoi(lstRes.front().c_str());lstRes.pop_front();
            info->name = lstRes.front();lstRes.pop_front();
            info->type = lstRes.front();lstRes.pop_front();
            info->md5 = lstRes.front();lstRes.pop_front();
            info->size = atoi(lstRes.front().c_str());lstRes.pop_front();
            info->dir = rq->dir;lstRes.pop_front();
            info->absolutePath = lstRes.front();lstRes.pop_front();

            info->filefd = open(info->absolutePath.c_str(), O_RDONLY);
            if(info->filefd <= 0){
                printf("file open failed %d\n", errno);
                return;
            }
            //map映射
            string strId = idBuf;
            m_mapFileidtoFileInfo.insert(strId, info);

    }
    //服务器map还存储文件信息
    //文件指针移动到pos
    lseek( info->filefd, rq->pos, SEEK_SET );
    info->pos = rq->pos;

    //返回文件头请求
    STRU_FILE_CONTENT_RQ contentrq;
    contentrq.userid = rq->userid;
    contentrq.fileid = rq->fileid;
    contentrq.len = read(info->filefd, contentrq.content, _DEF_BUFFER);
    SendData(clientfd, (char*)&contentrq, sizeof(contentrq));
}

void CLogic::GetUploadPosRq(sock_fd clientfd, char *szbuf, int nlen)
{
    STRU_GET_UPLOAD_POS_RQ* rq = (STRU_GET_UPLOAD_POS_RQ*)szbuf;
    FileInfo *info = nullptr;
    char idBuf[1000] = "";
    sprintf(idBuf, "%10d%10d", rq->userid, rq->fileid);

    if(!m_mapFileidtoFileInfo.find(idBuf,info)){
        //如果map没有，添加map
        //查数据库，获取信息
        char sqlBuf[1000] = "";
        sprintf(sqlBuf, "select t_file.f_id, f_name, f_type, f_md5, f_size, t_user_file.f_dir dir,f_path from t_file inner join t_user_file on t_file.f_id = t_user_file.f_id where t_user_file.u_id = %d and t_file.f_id = %d;", rq->userid, rq->fileid);
        list<string> lstRes;
        m_sql->SelectMysql( sqlBuf , 7 , lstRes );
        if(lstRes.size() == 0){
            //没有查询到 略
            cout << "select failed: " << sqlBuf << endl;
        }
        //建立文件映射 u_id f_id -> FileInfo
            info = new FileInfo;
            info->fileid = atoi(lstRes.front().c_str());lstRes.pop_front();
            info->name = lstRes.front();lstRes.pop_front();
            info->type = lstRes.front();lstRes.pop_front();
            info->md5 = lstRes.front();lstRes.pop_front();
            info->size = atoi(lstRes.front().c_str());lstRes.pop_front();
            info->dir = rq->dir;lstRes.pop_front();
            info->absolutePath = lstRes.front();lstRes.pop_front();

            info->filefd = open(info->absolutePath.c_str(), O_WRONLY);
            if(info->filefd <= 0){
                printf("file open failed %d\n", errno);
                return;
            }
            //map映射
            string strId = idBuf;
            m_mapFileidtoFileInfo.insert(strId, info);
    }
    info->pos = lseek( info->filefd, 0, SEEK_END);
    STRU_GET_UPLOAD_POS_RS rs;
    rs.fileid = info->fileid;
    rs.pos = info->pos;
    SendData(clientfd, (char*)&rs, sizeof(rs));
}

void CLogic::DownLoadFile(int clientfd, int userid, list<string> &lst)
{
    printf("Clientfd:%d, DownLoadFile;\n",clientfd);
    FileInfo *info = new FileInfo;
    info->type = lst.front();lst.pop_front();
    info->fileid = atoi(lst.front().c_str());lst.pop_front();
    info->name = lst.front();lst.pop_front();
    info->md5 = lst.front();lst.pop_front();
    info->size = atoi(lst.front().c_str());lst.pop_front();
    info->dir = lst.front();lst.pop_front();
    info->absolutePath = lst.front();lst.pop_front();

    info->filefd = open(info->absolutePath.c_str(), O_RDONLY);
    if(info->filefd <= 0){
        printf("file open failed %d\n", errno);
        return;
    }
    char idBuf[100] = "";
    sprintf(idBuf, "%10d%10d", userid, info->fileid);
    string strId = idBuf;
    m_mapFileidtoFileInfo.insert(strId, info);
    //返回文件头请求
    STRU_FILE_HEAD_RQ headrq;
    strcpy( headrq.dir, info->dir.c_str());
    headrq.fileid = info->fileid;
    strcpy( headrq.fileName, info->name.c_str());
    strcpy( headrq.fileType, info->type.c_str());
    strcpy( headrq.md5, info->md5.c_str());
    headrq.size = info->size;

    SendData(clientfd, (char*)&headrq, sizeof(headrq));
}

void CLogic::DownLoadFolder(int clientfd, int userid, int fileid, string name, string dir)
{
    printf("Clientfd:%d, DownLoadFolder;\n",clientfd);
    STRU_FOLDER_DOWNLOAD_RQ rq;
    string newDir = dir + name + "/";
    strcpy(rq.dir, dir.c_str());
    rq.fileid = fileid;
    strcpy(rq.fileName, name.c_str());
    SendData(clientfd, (char*)&rq, sizeof(rq));

    //查数据库，获取信息
    char sqlBuf[1000] = "";
    sprintf(sqlBuf, "select f_type, t_file.f_id, f_name, f_md5, f_size, t_user_file.f_dir dir,f_path from t_file inner join t_user_file on t_file.f_id = t_user_file.f_id where t_user_file.u_id = %d and t_user_file.f_dir = '%s';", userid, newDir.c_str());
    list<string> lst;
    m_sql->SelectMysql( sqlBuf , 7 , lst );
    while(lst.size() != 0){
        if(lst.front() == "file"){
            DownLoadFile(clientfd, userid, lst);
        }else{
            int fileid = atoi(lst.front().c_str());lst.pop_front();
            string type = lst.front();lst.pop_front();
            string name = lst.front();lst.pop_front();
            string md5 = lst.front();lst.pop_front();
            int size = atoi(lst.front().c_str());lst.pop_front();
            string dir = lst.front();lst.pop_front();
            string absolutePath = lst.front();lst.pop_front();
            DownLoadFolder(clientfd, userid, fileid, name, newDir);
        }
    }
}
void CLogic::GetShareByFile(int userId, int fileId, string dir)
{
    char sqlBuf[1000] = "";
    sprintf(sqlBuf, "insert into t_user_file values(%d, %d, '%s');",
            userId, fileId, dir.c_str());
    if(!m_sql->UpdataMysql(sqlBuf)){
        cout << "insert failed: " << sqlBuf << endl;
        return;
    }
}
void CLogic::GetShareByFolder(int userId, int fileId, string dir, int fromUserId, string fromDir, string name){
    GetShareByFile(userId, fileId, dir);
    //拼接路径 查表递归
    string newDir = dir + name + "/";
    string newFromDir = fromDir + name + "/";
    //查数据库 找到分享的文件 类型 文件id
    char sqlBuf[1000] = "";
    sprintf(sqlBuf, "select f_id, f_type, f_name from user_file_info where u_id = %d and f_dir = '%s';", fromUserId, newFromDir.c_str());
    list<string> lstRes;
    bool res = m_sql->SelectMysql(sqlBuf, 3, lstRes);
    if(!res){
        cout<< "select failed: " << sqlBuf << endl;
        return;
    }
    //不能递归？
    while(lstRes.size() != 0){
        int fileId = stoi(lstRes.front()); lstRes.pop_front();
        string type = lstRes.front(); lstRes.pop_front();
        string name = lstRes.front(); lstRes.pop_front();
        //根据文件类型 处理
        if(type == "file"){
            GetShareByFile(userId, fileId, newDir);
        }else{
            GetShareByFolder(userId, fileId, newDir, fromUserId, newFromDir, name);
        }
    }
}

void CLogic::ShareItem(int userId, int fileId, string dir, string time, int link)
{
    //查表
    char sqlBuf[1000] = "";
    list<string> lstRes;
    sprintf(sqlBuf, "select f_type, f_name from user_file_info where f_id = %d and u_id = %d and f_dir = '%s';", fileId, userId, dir.c_str());
    m_sql->SelectMysql(sqlBuf, 2, lstRes);
    while(lstRes.size() != 0){
        //看类别
        string type = lstRes.front(); lstRes.pop_front();
        string name = lstRes.front(); lstRes.pop_front();
        if(type == "file"){
            ShareFile(userId, fileId, dir, time, link);
        }else{
            ShareFolder(userId, fileId, dir, time, link, name);
        }
    }
//    sprintf(sqlBuf, "select f_type, f_name f_dir from user_file_info where f_id = %d and u_id = %d and f_dir = '%s';", fileId, userId, dir.c_str());
//    m_sql->SelectMysql(sqlBuf, 3, lstRes);
//    while(lstRes.size() != 0){
//        //看类别
//        string type = lstRes.front(); lstRes.pop_front();
//        string name = lstRes.front(); lstRes.pop_front();
//        string path = lstRes.front(); lstRes.pop_front();
//        if(type == "file"){
//            ShareFile(userId, fileId, dir+path, time, link);
//        }else{
//            ShareFolder(userId, fileId, dir+path, time, link, name);
//        }
//    }
}

void CLogic::ShareFile(int userId, int fileId, string dir, string time, int link)
{
    //插入分享表
    char sqlBuf[1000] = "";
    sprintf(sqlBuf, "insert into t_shareFile values( %d, %d, '%s', %d, null, '%s');",
            userId, fileId, dir.c_str(), link, time.c_str());
    bool res = m_sql->UpdataMysql(sqlBuf);
    if(!res){
        cout<< "update failed: " << sqlBuf << endl;
    }
}

void CLogic::ShareFolder(int userId, int fileId, string dir, string time, int link, string name)
{
    //插入分享表
    char sqlBuf[1000] = "";
    sprintf(sqlBuf, "insert into t_shareFile values( %d, %d, '%s', %d, null, '%s');",
            userId, fileId, dir.c_str(), link, time.c_str());
    bool res = m_sql->UpdataMysql(sqlBuf);
    if(!res){
        cout<< "update failed: " << sqlBuf << endl;
    }
    //查询当前路径下所有文件、文件夹 f_id, type name
    list<string> lstRes;
    string newDir = dir + name + "/";
    sprintf(sqlBuf, "select f_id, f_type, f_name from user_file_info where u_id = %d and f_dir = '%s';", userId, newDir.c_str());
    m_sql->SelectMysql(sqlBuf, 3, lstRes);
    while(lstRes.size() != 0){
        //看类别
        int fid = stoi(lstRes.front()); lstRes.pop_front();
        string type = lstRes.front(); lstRes.pop_front();
        string name = lstRes.front(); lstRes.pop_front();
        if(type == "file"){
            ShareFile(userId, fid, newDir, time, link);
        }else{
            ShareFolder(userId, fid, newDir, time, link, name);
        }
    }
}

void CLogic::DeleteItem(int userId, int fileId, string dir)
{
    //查文件信息
    //判断文件类型 select f_id , f_name , f_count , f_path , f_dir , f_type from user_file_info where u_id = %d and f_id = %d and f_dir = '%s';
    char sqlBuf[1000] = "";
    sprintf(sqlBuf, "select f_id , f_name , f_count , f_path , f_dir , f_type from user_file_info where u_id = %d and f_id = %d and f_dir = '%s';",
             userId, fileId, dir.c_str());
    list<string> lstRes;
    m_sql->SelectMysql(sqlBuf, 6, lstRes);
    if(lstRes.size() == 0) return;
    while(lstRes.size() > 0){
        int fileId = stoi(lstRes.front()); lstRes.pop_front();
        string name = lstRes.front(); lstRes.pop_front();
        int count = stoi(lstRes.front()); lstRes.pop_front();
        string path = lstRes.front(); lstRes.pop_front();
        string dir = lstRes.front(); lstRes.pop_front();
        string type = lstRes.front(); lstRes.pop_front();
        if(type == "file"){
            //删除文件操作
            DeleteFile(userId, fileId, name, count, path, dir);
        }else{
            //删除文件夹操作
            DeleteFolder(userId, fileId, name, count, path, dir);
        }
    }

}

void CLogic::DeleteFile(int userId, int fileId, string name, int count, string path, string dir)
{
    //删除用户文件关系表
    char sqlBuf[1000] = "";
    sprintf(sqlBuf, "delete from t_user_file where u_id = %d and f_id = %d and f_dir = '%s';", userId, fileId, dir.c_str());
    if(!m_sql->UpdataMysql(sqlBuf)){
        cout << "deleteFile sql error:%s" << sqlBuf;
    }
    if(count == 1){
        unlink(path.c_str());
    }
}

void CLogic::DeleteFolder(int userId, int fileId, string name, int count, string path, string dir)
{
    char sqlBuf[1000] = "";
    //删除用户文件关系表数据
    sprintf(sqlBuf, "delete from t_user_file where u_id = %d and f_id = %d and f_dir = '%s';", userId, fileId, dir.c_str());
    if(!m_sql->UpdataMysql(sqlBuf)){
        cout << "deleteFolder sql error:%s" << sqlBuf;
    }

    //删除 文件夹内文件
    string strDir = dir + name + "/";
    sprintf(sqlBuf, "select f_id , f_name , f_count , f_path , f_dir , f_type from user_file_info where u_id = %d and f_id = %d and f_dir = '%s';",
             userId, fileId, strDir.c_str());
    list<string> lstRes;
    m_sql->SelectMysql(sqlBuf, 6, lstRes);
    if(lstRes.size() == 0) return;
    while(lstRes.size() > 0){
        int fileId = stoi(lstRes.front()); lstRes.pop_front();
        string name = lstRes.front(); lstRes.pop_front();
        int count = stoi(lstRes.front()); lstRes.pop_front();
        string path = lstRes.front(); lstRes.pop_front();
        string dir = lstRes.front(); lstRes.pop_front();
        string type = lstRes.front(); lstRes.pop_front();
        if(type == "file"){
            //删除文件操作
            DeleteFile(userId, fileId, name, count, strDir, dir);
        }else{
            //删除文件夹操作
            DeleteFolder(userId, fileId, name, count, strDir, dir);
        }
    }
}


