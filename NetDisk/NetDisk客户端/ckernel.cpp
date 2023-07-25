#include "ckernel.h"
#include <QDebug>
#include <QMessageBox>
#include "TcpClientMediator.h"
#include "TcpServerMediator.h"
#include "md5.h"
#include <QDir>
#include <QCoreApplication>
#include <QThread>

#define MD5_KEY "1234"
string getMD5(QString val){
    QString str = QString("%1_%2").arg(val).arg(MD5_KEY);
    MD5 md(str.toStdString());
    qDebug() << md.toString().c_str();
    return md.toString();
}

#include<QTextCodec>

// QString -> char* gb2312
void Utf8ToGB2312( char* gbbuf , int nlen ,QString& utf8)
{
    //转码的对象
    QTextCodec * gb2312code = QTextCodec::codecForName( "gb2312");
    //QByteArray char 类型数组的封装类 里面有很多关于转码 和 写IO的操作
    QByteArray ba = gb2312code->fromUnicode( utf8 );// Unicode -> 转码对象的字符集

    strcpy_s ( gbbuf , nlen , ba.data() );
}
string getFileMD5(QString path){
    //打开文件
    qDebug() << path;
    FILE *pFile = nullptr;
    //utf-8 -> ascii
    char buf[1000] = "";
    Utf8ToGB2312(buf, 1000, path);
    pFile = fopen(buf, "rb");
    if(!pFile){
        qDebug() << "getFileMD5 open file failed";
        return string();
    }
    //读取，拼接MD5
    int len = 0;
    MD5 md;
    do{
        len = fread(buf, 1, 1000, pFile);
        //防止因为文件过大 导致获取MD5的时间过长, 其他事件无法执行*
        QCoreApplication::processEvents( QEventLoop::AllEvents , 100);
        md.update(buf,len);//拼接字符串 生成MD5
    }while(len > 0);
    fclose(pFile);
    qDebug() << "md5:" << md.toString().c_str();
    return md.toString();
}

// char* gb2312 --> QString utf8
QString GB2312ToUtf8( char* gbbuf )
{
    //转码的对象
    QTextCodec * gb2312code = QTextCodec::codecForName( "gb2312");
    //QByteArray char 类型数组的封装类 里面有很多关于转码 和 写IO的操作
    return gb2312code->toUnicode( gbbuf );// 转码对象的字符集 -> Unicode
}

#define NetMap(a) m_netPackMap[a - _DEF_PROTOCOL_BASE]
void CKernel::setNetMap()
{
    memset(m_netPackMap, 0, sizeof(PFUN)*_DEF_PROTOCOL_COUNT);

    NetMap(_DEF_PACK_REGISTER_RS) = &CKernel::slot_dealRegistRs;
    NetMap(_DEF_PACK_LOGIN_RS) = &CKernel::slot_dealLoginRs;
    NetMap(_DEF_FILE_INFO) = &CKernel::slot_dealFileInfo;
    NetMap(_DEF_PACK_FILE_HEAD_RQ) = &CKernel::slot_dealFileHeadRq;
    NetMap(_DEF_PACK_FILE_CONTENT_RQ) = &CKernel::slot_dealFileContentRq;
    NetMap(_DEF_UPLOAD_FILE_RS) = &CKernel::slot_dealUploadFileHeadRs;
    NetMap(_DEF_PACK_FILE_CONTENT_RS) = &CKernel::slot_dealFileContentRs;
    NetMap(_DEF_ADD_FOLDER_RS) = &CKernel::slot_dealAddFolderRs;
    NetMap(_DEF_QUICK_UPLOAD_RS) = &CKernel::slot_dealQuickUploadFileRs;
    NetMap(_DEF_PACK_DELETE_FILE_RS) = &CKernel::slot_dealDeleteFileRs;
    NetMap(_DEF_PACK_SHARE_FILE_RS) = &CKernel::slot_dealShareFileRs;
    NetMap(_DEF_PACK_MY_SHARE_RS) = &CKernel::slot_dealMyShareRs;
    NetMap(_DEF_PACK_GET_SHARE_RS) = &CKernel::slot_dealGetShareRs;
    NetMap(_DEF_FOLDER_DOWNLOAD_RQ) = &CKernel::slot_dealFolderDownLoadRq;
    NetMap(_DEF_GET_UPLOAD_POS_RS) = &CKernel::slot_dealGetUploadPosRs;

}

CKernel::CKernel(QObject *parent) : QObject(parent), m_quick(false)
{
    setConfig();
    setNetMap();

    m_sql = new CSqlite;
    m_mainDialog  = new MainDialog;
    //m_mainDialog->show();
    m_tcpClient = new TcpClientMediator;

    m_loginDialog = new LoginDialog;
    m_loginDialog->show();

    m_tcpClient->OpenNet(m_ip.toStdString().c_str(),m_port);

    connect(m_tcpClient, SIGNAL(SIG_ReadyData(uint,char*,int)),
            this, SLOT(slot_clientReadyData(uint,char*,int)));

    connect(m_mainDialog, SIGNAL(SIG_close()),
            this , SLOT(slot_destroyInstance()));
    connect(m_mainDialog, SIGNAL(SIG_downloadFile(int)),
            this, SLOT(slot_downloadFile(int)));
    connect(this, SIGNAL(SIG_updateFileProgress(int,int)),
            m_mainDialog, SLOT(slot_updateFileProgress(int,int)));
    connect(m_mainDialog, SIGNAL(SIG_uploadFile(QString)),
            this, SLOT(slot_uploadFile(QString)));
    connect(m_mainDialog, SIGNAL(SIG_uploadFolder(QString)),
            this, SLOT(slot_uploadFolder(QString)));
    connect(this, SIGNAL(SIG_updateUploadFileProgress(int,int)),
            m_mainDialog, SLOT(slot_updateUploadFileProgress(int,int)));
    connect(m_mainDialog, SIGNAL(SIG_addFolder(QString)),
            this, SLOT(slot_addFolder(QString)));
    connect(m_mainDialog, SIGNAL(SIG_changePath(QString)),
            this, SLOT(slot_changePath(QString)));
    connect(m_mainDialog, SIGNAL(SIG_deleteFile(QString,QVector<int>)),
            this, SLOT(slot_deleteFile(QString,QVector<int>)));
    connect(m_mainDialog, SIGNAL(SIG_shareFile(QString,QVector<int>)),
            this, SLOT(slot_shareFile(QString,QVector<int>)));
    connect(m_mainDialog, SIGNAL(SIG_getShare(QString,int)),
            this, SLOT(slot_getShare(QString,int)));
    connect(m_mainDialog, SIGNAL(SIG_setUploadPause(int,int)),
            this, SLOT(slot_setUploadPause(int,int)));
    connect(m_mainDialog, SIGNAL(SIG_setDownloadPause(int,int)),
            this, SLOT(slot_setDownloadPause(int,int)));

    connect(m_loginDialog, SIGNAL(SIG_close()),
            this , SLOT(slot_destroyInstance()));
    connect(m_loginDialog, SIGNAL(SIG_registerCommit(QString,QString,QString)),
            this , SLOT(slot_registerCommit(QString,QString,QString)));
    connect(m_loginDialog, SIGNAL(SIG_loginCommit(QString,QString)),
            this , SLOT(slot_loginCommit(QString, QString)));



}


#include <QFileInfo>
#include <QSettings>
//设置配置文件
void CKernel::setConfig()
{
    /// windows *.ini -->config.ini
    /// [net] 组名
    /// key = value 键值对
    /// ip = "192.168.5.197"
    /// port = 8003
    /// 保存在哪？ exe 的目录下面
    /// exe 的目录 获取
    /// D:/QtProjects/NetDisk/build/debug
    QString path = QCoreApplication::applicationDirPath()+"/config.ini";
    //可以考虑 有就读取，没有就写入默认值
    m_ip = "192.168.5.197";
    m_port = 8003;
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

    //查看是否有默认路径
    QString sysPath = QCoreApplication::applicationDirPath()+"/NetDisk/";
    QDir dir;
    if( !dir.exists(sysPath) ){
        dir.mkdir(sysPath);
    }
    m_curPath = '/';
    m_sysPath = QCoreApplication::applicationDirPath()+"/NetDisk";
}

void CKernel::slot_destroyInstance()
{
    qDebug() << __func__;
    m_quick = true;
    //回收网络
    m_tcpClient->CloseNet();
    delete m_tcpClient;
    delete m_mainDialog;
}
//处理接收到的数据
void CKernel::slot_clientReadyData(unsigned int lSendIP, char *buf, int nlen)
{
    char *tmp = buf;
    int type = *(int*)tmp;
    //类型合法
    if(type>=_DEF_PROTOCOL_BASE && type <= _DEF_PROTOCOL_COUNT + _DEF_PROTOCOL_BASE){
        PFUN pf = NetMap(type);
        if(pf){
            (this->*pf)(lSendIP, buf, nlen);
        }
    }
    delete[] buf;
}
//
void CKernel::slot_serverReadyData(unsigned int lSendIP, char *buf, int nlen)
{

}
//注册回复
void CKernel::slot_dealRegistRs(unsigned int lSendIP, char *buf, int nlen)
{
    qDebug() << __func__;
    STRU_REGISTER_RS* rs = (STRU_REGISTER_RS*)buf;
    switch (rs->result) {
    case tel_is_exist:
        QMessageBox::about(m_loginDialog, "注册提示", "电话号已存在");
        break;
    case name_is_exist:
        QMessageBox::about(m_loginDialog, "注册提示", "昵称已存在");
        break;
    case register_success:
        QMessageBox::about(m_loginDialog, "注册提示", "注册成功");
        break;
    default:
        break;
    }
}
//登录回复
void CKernel::slot_dealLoginRs(unsigned int lSendIP, char *buf, int nlen)
{
    qDebug() << __func__;
    STRU_LOGIN_RS* rs = (STRU_LOGIN_RS*)buf;
    switch (rs->result) {
    case user_not_exist:
        QMessageBox::about(m_loginDialog, "登录提示", "用户不存在");
        break;
    case password_error:
        QMessageBox::about(m_loginDialog, "登录提示", "密码错误");
        break;
    case login_success:
        QMessageBox::about(m_loginDialog, "登录提示", "登录成功");
        //窗口切换
        m_loginDialog->hide();
        m_mainDialog->show();
        //信息保存
        m_name = rs->name;
        m_id = rs->userid;
        m_mainDialog->slot_setInfo(m_name);
        //文件列表请求
        updateFileList();
        initDatabase(m_id);
        m_mainDialog->deleteShareList();
        slot_refreshMyShare();
        break;
    }
}
//文件信息
void CKernel::slot_dealFileInfo(unsigned int lSendIP, char *buf, int nlen)
{
    //拆包
    STRU_FILE_INFO* info = (STRU_FILE_INFO*)buf;
//    //获取信息
//    qDebug() << "fileName:" << info->fileName << " "
//               <<"UploadTime:" << info->uploadTime << " "
//                <<"Size:" << info->size <<" "
//                <<"Type:" << info->fileType;
    //判断是否为当前路径
    FileInfo fileInfo;
    fileInfo.dir = QString::fromStdString( info->dir );
    fileInfo.fileid = info->fileid;
    fileInfo.fileType = QString::fromStdString( info->fileType );
    fileInfo.md5 = QString::fromStdString( info->md5 );
    fileInfo.name = QString::fromStdString( info->fileName );
    fileInfo.time = QString::fromStdString( info->uploadTime );
    fileInfo.size = info->size;
    //添加控件显示到界面
    m_mainDialog->slot_insertFileInfo(fileInfo);
}

void CKernel::slot_dealFileHeadRq(unsigned int lSendIP, char *buf, int nlen)
{
    //拆包
    STRU_FILE_HEAD_RQ* rq = (STRU_FILE_HEAD_RQ*)buf;
    //创建info
    FileInfo fileInfo;
    fileInfo.dir = QString::fromStdString( rq->dir );
    fileInfo.fileid = rq->fileid;
    fileInfo.fileType = QString::fromStdString( rq->fileType );
    fileInfo.md5 = QString::fromStdString( rq->md5 );
    fileInfo.name = QString::fromStdString( rq->fileName );
    //fileInfo.time = QString::fromStdString( rq->uploadTime );
    fileInfo.size = rq->size;
    //绝对路径 默认路径 exe同级 /NetDisk
    fileInfo.absolutePath = m_sysPath + fileInfo.dir + fileInfo.name;
    QDir dir;
    QStringList pathList = fileInfo.dir.split("/");
    QString path = m_sysPath;
    for(int i=0; i<pathList.size(); ++i){
        if( ((QString)(pathList.at(i))).isEmpty() ) continue;
        path += "/" + pathList.at(i);
        if(!dir.exists(path)){
            dir.mkdir(path);
        }
    }

    //转换为 ANSI linux和qt都是utf-8 windows文件路径是ASSIC码，要转换
    char pathBuf[1000] = "";
    Utf8ToGB2312(pathBuf, 1000, fileInfo.absolutePath);
    //打开文件
    fileInfo.pFile = fopen(pathBuf, "wb");
    if( !fileInfo.pFile ){
        qDebug() << "文件打开失败" << fileInfo.absolutePath;
        return;
    }
    //添加下载控件
    m_mainDialog->slot_insertDownloadFile(fileInfo);
    //添加到map映射
    slot_writeDownloadTask(fileInfo);
    m_mapFileidToFileInfo[fileInfo.fileid] = fileInfo;
    //返回文件头回复
    STRU_FILE_HEAD_RS rs;
    rs.fileid = rq->fileid;
    rs.result = 1;//0打开文件失败
    rs.userid = m_id;
    SendData((char*)&rs, sizeof(rs));
}

void CKernel::slot_dealFolderDownLoadRq(unsigned int lSendIP, char *buf, int nlen)
{
    qDebug() << __func__;
    STRU_FOLDER_DOWNLOAD_RQ *rq = (STRU_FOLDER_DOWNLOAD_RQ*)buf;
    QDir dr;
    QStringList pathList = QString::fromStdString(rq->dir).split("/");
    QString path = m_sysPath;
    for(int i=0; i<pathList.size(); ++i){
        if( ((QString)(pathList.at(i))).isEmpty() ) continue;
        path += "/" + pathList.at(i);
        qDebug() << "path: " << path;
        if(!dr.exists(path)){
            dr.mkdir(path);
        }
    }
}

void CKernel::slot_dealFileContentRq(unsigned int lSendIP, char *buf, int nlen)
{
    STRU_FILE_CONTENT_RQ* rq = (STRU_FILE_CONTENT_RQ*)buf;
    FileInfo& info = m_mapFileidToFileInfo[rq->fileid];
    while(info.isPause){
        QThread::msleep(100);
        QCoreApplication::processEvents( QEventLoop::AllEvents , 100 );
        if(m_quick) return;
    }
    //1 2一次写多少 3写多少次 4返回成功写入次数
    int len = fwrite( rq->content, 1, rq->len, info.pFile );
    //qDebug() << "write:"<<len;
    //文件内容回复
    STRU_FILE_CONTENT_RS rs;
    rs.len = rq->len;
    rs.fileid = rq->fileid;
    rs.userid = rq->userid;
    //判断是否写入成功
    if(len != rq->len){
        //失败
        fseek(info.pFile, -1*len, SEEK_CUR);
        rs.result = 0;
    }else{
        info.pos += len;
        Q_EMIT SIG_updateFileProgress(info.fileid, info.pos);
        rs.result = 1;
    }
    //判断是否写入完成
    if(info.pos >= info.size){
        fclose(info.pFile);
        slot_deleteDownloadTask(info);
        m_mapFileidToFileInfo.erase(info.fileid);
    }
    SendData((char*)&rs, sizeof(rs));
}

void CKernel::slot_dealUploadFileHeadRs(unsigned int lSendIP, char *buf, int nlen)
{
    //拆包
    STRU_UPLOAD_FILE_RS *rs = (STRU_UPLOAD_FILE_RS*)buf;
    //通过md5的map 添加 filedid的map
    if(m_mapMD5ToFileInfo.count(rs->md5) == 0) return;
    FileInfo &info = m_mapMD5ToFileInfo[rs->md5];

    info.fileid = rs->fileid;

    m_mapFileidToFileInfo[rs->fileid] = info;

    //添加上传页面控件
    slot_writeUploadTask(info);
    m_mainDialog->slot_insertUploadFile(info);

    //读文件
    STRU_FILE_CONTENT_RQ rq;
    rq.len = fread(rq.content, 1, _DEF_BUFFER, info.pFile);
    rq.fileid = rs->fileid;
    rq.userid = rs->userid;
    //发送内容请求包
    SendData((char*)&rq, sizeof(rq));
    //md5的map去除元素
    m_mapMD5ToFileInfo.erase(rs->md5);
}

void CKernel::slot_dealFileContentRs(unsigned int lSendIP, char *buf, int nlen)
{
    //拆包
    STRU_FILE_CONTENT_RS *rs = (STRU_FILE_CONTENT_RS*)buf;
    //通过filedid查map 得到FileInfo
    if(m_mapFileidToFileInfo.count(rs->fileid) == 0) return;
    FileInfo &info = m_mapFileidToFileInfo[rs->fileid];
    while(info.isPause){
        QThread::msleep(100);
        QCoreApplication::processEvents( QEventLoop::AllEvents , 100 );
        if(m_quick) return;
    }
    STRU_FILE_CONTENT_RQ rq;
    //判断返回结果
    if(rs->result == 0){
        //失败，跳回
        qDebug() << "failed upload" ;
    }else{
        //成功，看是否结束
        info.pos += rs->len;
        //发送页面更新信号
        Q_EMIT SIG_updateUploadFileProgress(rs->fileid, info.pos);
        if(info.pos >= info.size){
            //判断是否为当前路径
            if(info.dir == m_curPath){
                updateFileList();
            }
            //写入完成 不需要发送包了
            fclose(info.pFile);
            slot_deleteUploadTask(info);
            m_mapFileidToFileInfo.erase(rs->fileid);
            return;
        }
    }
    rq.len = fread(rq.content, 1, _DEF_BUFFER, info.pFile);
    rq.fileid = rs->fileid;
    rq.userid = rs->userid;
    //发送内容请求包
    SendData((char*)&rq, sizeof(rq));
}

void CKernel::slot_dealAddFolderRs(unsigned int lSendIP, char *buf, int nlen)
{
    STRU_ADD_FOLDER_RS *rs = (STRU_ADD_FOLDER_RS*)buf;
    if(rs->result == 1){
        updateFileList();
    }
}

void CKernel::slot_dealQuickUploadFileRs(unsigned int lSendIP, char *buf, int nlen)
{
    //拆包
    STRU_QUICK_UPLOAD_RS *rs = (STRU_QUICK_UPLOAD_RS*)buf;
    if(rs->result == 0) return;

    if(m_mapMD5ToFileInfo.count(rs->md5) == 0) return;
    FileInfo info = m_mapMD5ToFileInfo[rs->md5];

    updateFileList();
    m_mainDialog->slot_insertUploadComplete(info);
    m_mapMD5ToFileInfo.erase(rs->md5);
}

void CKernel::slot_dealDeleteFileRs(unsigned int lSendIP, char *buf, int nlen)
{
    STRU_DELETE_FILE_RS* rq = (STRU_DELETE_FILE_RS*)buf;
    if(rq->result == 0) return;
    QString strPath = QString::fromStdString( rq->dir );
    if(strPath == m_curPath){
        updateFileList();
    }
}

void CKernel::slot_dealShareFileRs(unsigned int lSendIP, char *buf, int nlen)
{
    qDebug() << __func__;
    STRU_SHARE_FILE_RS* rs = (STRU_SHARE_FILE_RS*)buf;
    if(rs->result == 0) return;
    //刷新
    m_mainDialog->deleteShareList();
    slot_refreshMyShare();
}

void CKernel::slot_dealMyShareRs(unsigned int lSendIP, char *buf, int nlen)
{
    STRU_MY_SHARE_RS* rs = (STRU_MY_SHARE_RS*)buf;
    for(int i=0; i<rs->itemCount; ++i){
        m_mainDialog->slot_insertShare(
                    rs->items[i].name, FileInfo::getSize(rs->items[i].size),
                    rs->items[i].time, QString::number(rs->items[i].shareLink));
    }
}

void CKernel::slot_dealGetShareRs(unsigned int lSendIP, char *buf, int nlen)
{
    STRU_GET_SHARE_RS* rs = (STRU_GET_SHARE_RS*)buf;
    if(!rs->result) return;
    if(QString::fromStdString(rs->dir) == m_curPath){
        updateFileList();
    }
}

void CKernel::slot_dealGetUploadPosRs(unsigned int lSendIP, char *buf, int nlen)
{
    STRU_GET_UPLOAD_POS_RS* rs = (STRU_GET_UPLOAD_POS_RS*)buf;
    if(!rs->result) return;

    //更新进度条
    m_mainDialog->slot_updateUploadFileProgress( rs->fileid, rs->pos );
}
#include<QFileInfo>
#include<QDateTime>
void CKernel::slot_uploadFile(QString path)
{
    QFileInfo fileInfo(path);
    //fileInfo.fileName();
    //fileInfo.size();
    //创建文件结构体
    FileInfo info;
    info.absolutePath = path;
    info.dir = m_curPath;
    //info.fileid;

    info.md5 = QString::fromStdString(getFileMD5(path));
    info.name = fileInfo.fileName();
    //info.pFile = ;
    info.size = fileInfo.size();
    info.time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    info.fileType = "file";
    //打开文件
    char buf[1000] = "";
    Utf8ToGB2312(buf, 1000, path);
    info.pFile = fopen(buf, "rb");
    //添加到map
    m_mapMD5ToFileInfo[info.md5.toStdString()] = info;
    //发送上传文件请求头 协议赋值
    STRU_UPLOAD_FILE_RQ rq;
    //有中文要借助临时变量 存一下，无中文 直接strcpy即可
    std::string strDir = info.dir.toStdString();
    strcpy(rq.dir, strDir.c_str());
    std::string strName = info.name.toStdString();
    strcpy(rq.fileName, strName.c_str());
    strcpy(rq.fileType, info.fileType.toStdString().c_str());
    strcpy(rq.md5, info.md5.toStdString().c_str());
    rq.size = info.size;
    strcpy(rq.time, info.time.toStdString().c_str());
    rq.userid = m_id;

    SendData((char*)&rq, sizeof(rq));
}
void CKernel::slot_uploadFile(QString path, QString dir)
{
    QFileInfo fileInfo(path);
    //fileInfo.fileName();
    //fileInfo.size();
    //创建文件结构体
    FileInfo info;
    info.absolutePath = path;
    info.dir = dir;
    //info.fileid;

    info.md5 = QString::fromStdString(getFileMD5(path));
    info.name = fileInfo.fileName();
    //info.pFile = ;
    info.size = fileInfo.size();
    info.time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    info.fileType = "file";
    //打开文件
    char buf[1000] = "";
    Utf8ToGB2312(buf, 1000, path);
    info.pFile = fopen(buf, "rb");
    //添加到map
    m_mapMD5ToFileInfo[info.md5.toStdString()] = info;
    //发送上传文件请求头 协议赋值
    STRU_UPLOAD_FILE_RQ rq;
    //有中文要借助临时变量 存一下，无中文 直接strcpy即可
    std::string strDir = info.dir.toStdString();
    strcpy(rq.dir, strDir.c_str());
    std::string strName = info.name.toStdString();
    strcpy(rq.fileName, strName.c_str());
    strcpy(rq.fileType, info.fileType.toStdString().c_str());
    strcpy(rq.md5, info.md5.toStdString().c_str());
    rq.size = info.size;
    strcpy(rq.time, info.time.toStdString().c_str());
    rq.userid = m_id;

    SendData((char*)&rq, sizeof(rq));
}

void CKernel::slot_uploadFolder(QString path)
{
    slot_uploadFolder(path, m_curPath);
}
void CKernel::slot_uploadFolder(QString path, QString dir)
{
    qDebug() << "path: " << path << "dir: " << dir;
    QDir dr(path);
    QFileInfo info(path);
    //创建文件夹
   slot_addFolder(info.fileName(), dir);
   //向下遍历获取
   QFileInfoList lst = dr.entryInfoList();
   QString newDir = dir + info.fileName() + "/";
   for(int i=0; i<lst.size(); ++i){
       QFileInfo file = lst.at(i);
       if(file.fileName() == ".") continue;
       if(file.fileName() == "..") continue;
       //判断类型
       if(file.isFile()){
           slot_uploadFile(file.absoluteFilePath(), newDir);
       }
       if(file.isDir()){
           slot_uploadFolder(file.absoluteFilePath(), newDir);
       }
   }
}

//注册提交槽函数
void CKernel::slot_registerCommit(QString tel, QString pwd, QString name)
{
    STRU_REGISTER_RQ rq;
    std::string telStr = tel.toStdString();
    strcpy( rq.tel, telStr.c_str() );

    std::string nameStr = name.toStdString();
    strcpy( rq.name, nameStr.c_str() );

    std::string pwdStr = getMD5(pwd);
    strcpy( rq.password, pwdStr.c_str() );
    //发送
    SendData( (char*)&rq, sizeof(rq) );
}

//登录提交槽函数
void CKernel::slot_loginCommit(QString tel, QString pwd)
{
    STRU_LOGIN_RQ rq;
    std::string telStr = tel.toStdString();
    strcpy( rq.tel, telStr.c_str() );

    std::string pwdStr = getMD5(pwd);
    strcpy( rq.password, pwdStr.c_str() );
    //发送
    SendData( (char*)&rq, sizeof(rq) );
}
//发送下载文件请求
void CKernel::slot_downloadFile(int fileid)
{
    STRU_DOWNLOAD_RQ rq;
    rq.fileid = fileid;
    rq.userid = m_id;
    std::string strDir = m_curPath.toStdString();
    strcpy(rq.dir, strDir.c_str());
    SendData( (char*)&rq, sizeof(rq) );
}

void CKernel::slot_addFolder(QString name)
{

    //发送新建文件夹请求 协议赋值
    STRU_ADD_FOLDER_RQ rq;
    std::string tmpDir = m_curPath.toStdString();
    strcpy(rq.dir, tmpDir.c_str());
    std::string tmpName = name.toStdString();
    strcpy(rq.fileName, tmpName.c_str());
    QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    strcpy(rq.time, time.toStdString().c_str());
    strcpy(rq.fileType, "dir");
    rq.userid = m_id;
    rq.size = 0;

    SendData((char*)&rq, sizeof(rq));
}
void CKernel::slot_addFolder(QString name, QString dir)
{
    qDebug() << "name: " << name << "dir: " << dir;
    //发送新建文件夹请求 协议赋值
    STRU_ADD_FOLDER_RQ rq;
    std::string tmpDir = dir.toStdString();
    strcpy(rq.dir, tmpDir.c_str());
    std::string tmpName = name.toStdString();
    strcpy(rq.fileName, tmpName.c_str());
    QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    strcpy(rq.time, time.toStdString().c_str());
    strcpy(rq.fileType, "dir");
    rq.userid = m_id;
    rq.size = 0;

    SendData((char*)&rq, sizeof(rq));
}

void CKernel::slot_changePath(QString path)
{
    //更改路径
    m_curPath = path;
    updateFileList();
}

void CKernel::slot_deleteFile(QString path, QVector<int> fileidArray)
{
    int len = sizeof(STRU_DELETE_FILE_RQ) + fileidArray.size()*sizeof(int);
    STRU_DELETE_FILE_RQ* rq = (STRU_DELETE_FILE_RQ*)malloc(len);
    rq->init();
    string strDir = path.toStdString();
    strcpy( rq->dir , strDir.c_str());
    rq->userid = m_id;
    rq->fileCount = fileidArray.size();
    for(int i=0; i<fileidArray.size(); ++i){
        rq->fileidArray[i] = fileidArray[i];
    }
    SendData((char*)rq, len);
    free(rq);
}

void CKernel::slot_shareFile(QString path, QVector<int> fileidArray)
{
    int len = sizeof(STRU_SHARE_FILE_RQ) + fileidArray.size()*sizeof(int);
    STRU_SHARE_FILE_RQ* rq = (STRU_SHARE_FILE_RQ*)malloc(len);
    rq->init();
    QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    strcpy(rq->shareTime, time.toStdString().c_str());
    string strDir = path.toStdString();
    strcpy( rq->dir , strDir.c_str());
    rq->userid = m_id;
    rq->itemCount = fileidArray.size();
    for(int i=0; i<fileidArray.size(); ++i){
        rq->fileidArray[i] = fileidArray[i];
        qDebug() << "share fileId: " << fileidArray[i];
    }
    SendData((char*)rq, len);
    free(rq);
}

void CKernel::slot_refreshMyShare()
{
    qDebug() << __func__;
    STRU_MY_SHARE_RQ rq;
    rq.userid = m_id;
    SendData((char*)&rq, sizeof(rq));
}

void CKernel::slot_getShare(QString path, int link)
{
    STRU_GET_SHARE_RQ rq;
    //兼容中文
    string dir = path.toStdString();
    strcpy(rq.dir, dir.c_str());
    rq.shareLink = link;
    rq.userid = m_id;
    SendData((char*)&rq, sizeof(rq));
}

void CKernel::slot_setUploadPause(int fileId, int pauseFlag)
{
    qDebug() << __func__ ;
    if(m_mapFileidToFileInfo.count(fileId) > 0){
        //map里有 暂停恢复
        m_mapFileidToFileInfo[fileId].isPause = pauseFlag;
    }else{
        //map里没有 断点续传 , pauseFlag只能是1 因为只能继续传输
        if(pauseFlag == 0){
            //直接传输文件内容即可，因为服务端处理就已经有文件信息映射了
            FileInfo info = m_mainDialog->slot_getUploadFileInfoByFileID(fileId);
            //转换为 ANSI linux和qt都是utf-8 windows文件路径是ASSIC码，要转换
            char pathBuf[1000] = "";
            Utf8ToGB2312(pathBuf, 1000, info.absolutePath);
            //打开文件
            info.pFile = fopen(pathBuf, "rb");
            info.isPause = 0;
            fseek(info.pFile, info.pos, SEEK_SET);
            m_mapFileidToFileInfo[info.fileid] = info;
            STRU_FILE_CONTENT_RQ rq;
            rq.len = fread(rq.content, 1, _DEF_BUFFER, info.pFile);
            rq.fileid = fileId;
            rq.userid = m_id;
            //发送内容请求包
            SendData((char*)&rq, sizeof(rq));
        }
    }
}

void CKernel::slot_setDownloadPause(int fileId, int pauseFlag)
{
    if(m_mapFileidToFileInfo.count(fileId) > 0){
        //map里有 暂停恢复
        m_mapFileidToFileInfo[fileId].isPause = pauseFlag;
    }else{
        //map里没有 断点续传 , pauseFlag只能是0 因为只能继续传输
        if(pauseFlag == 0){
            //通过控件获取
            FileInfo fileInfo = m_mainDialog->slot_getDownloadFileInfoByFileID(fileId);
            QDir dir;
            QStringList pathList = fileInfo.dir.split("/");
            QString path = m_sysPath;
            for(int i=0; i<pathList.size(); ++i){
                if( ((QString)(pathList.at(i))).isEmpty() ) continue;
                path += "/" + pathList.at(i);
                if(!dir.exists(path)){
                    dir.mkdir(path);
                }
            }

            //转换为 ANSI linux和qt都是utf-8 windows文件路径是ASSIC码，要转换
            char pathBuf[1000] = "";
            Utf8ToGB2312(pathBuf, 1000, fileInfo.absolutePath);
            //打开文件
            fileInfo.pFile = fopen(pathBuf, "ab");//追加打开，w会覆盖原内容，a是文件末尾开始写入
            if( !fileInfo.pFile ){
                qDebug() << "文件打开失败" << fileInfo.absolutePath;
                return;
            }
            //添加到map映射,暂停改为
            fileInfo.isPause = 0;
            m_mapFileidToFileInfo[fileInfo.fileid] = fileInfo;
            //发送续下载协议
            STRU_CONTINUE_DOWNLOAD_RQ rq;
            string strDir = fileInfo.dir.toStdString();
            strcpy( rq.dir , strDir.c_str() );
            rq.fileid = fileId;
            rq.pos = fileInfo.pos;
            rq.userid = m_id;
            SendData((char*)&rq, sizeof(rq));
        }
    }
}

void CKernel::initDatabase(int id)
{
    QString path = QCoreApplication::applicationDirPath() + "/database/";
    QDir dir;
    //检查database文件夹是否存在，不存在则创建
    if(!dir.exists(path)){
        dir.mkdir(path);
    }
    path = path + QString("%1.db").arg(id);
    //检查数据库文件是否存在
    QFileInfo info(path);
    if(info.exists()){
        //有，连接数据库
        m_sql->ConnectSql(path);
        //查询
        QList<FileInfo> lstUpload;
        QList<FileInfo> lstDownload;
        slot_getUploadTask(lstUpload);
        slot_getDownloadTask(lstDownload);

        //显示界面
        for(FileInfo& info : lstUpload){
            //文件不存在直接跳过
            QFileInfo fileInfo(info.absolutePath);
            if(!fileInfo.exists())
                continue;
            info.isPause = 1;
            m_mainDialog->slot_insertUploadFile(info);

            //获取进度，在服务端需要发协议
            STRU_GET_UPLOAD_POS_RQ rq;
            rq.fileid = info.fileid;
            rq.userid = m_id;
            string strDir = info.dir.toStdString();
            strcpy(rq.dir , strDir.c_str());
            SendData( (char*)&rq, sizeof(rq) );
        }
        for(FileInfo& info : lstDownload){
            //文件不存在直接跳过
            QFileInfo fileInfo(info.absolutePath);
            if(!fileInfo.exists())
                continue;
            info.isPause = 1;
            info.pos = fileInfo.size();
            m_mainDialog->slot_insertDownloadFile(info);
            //在本地，直接查看
            m_mainDialog->slot_updateFileProgress(info.fileid, fileInfo.size());
        }
    }else{
        //没有则创建
        QFile file(path);
        if(!file.open(QIODevice::WriteOnly)) return;
        file.close();

        m_sql->ConnectSql(path);
        //建表
        QString sqlstr = QString("create table t_upload (\
                                f_id int,\
                                f_name varchar(260),\
                                f_dir varchar(260),\
                                f_absolutePath varchar(260),\
                                f_size int,\
                                f_md5 varchar(40),\
                                f_time varchar(40),\
                                f_type varchar(10) );");
        m_sql->UpdateSql(sqlstr);
        sqlstr = QString("create table t_download (\
                            f_id int,\
                            f_name varchar(260),\
                            f_dir varchar(260),\
                            f_absolutePath varchar(260),\
                            f_size int,\
                            f_md5 varchar(40),\
                            f_time varchar(40),\
                            f_type varchar(10) );");
        m_sql->UpdateSql(sqlstr);
    }
}

void CKernel::slot_writeUploadTask(FileInfo &info)
{
        QString sqlstr = QString("insert into t_upload values(%1,'%2','%3','%4',%5,'%6','%7','%8')").arg(info.fileid).arg(info.name).arg(info.dir).arg(info.absolutePath).arg(info.size).arg(info.md5).arg(info.time).arg(info.fileType);
        m_sql->UpdateSql(sqlstr);
}

void CKernel::slot_writeDownloadTask(FileInfo &info)
{
    QString sqlstr = QString("insert into t_download values(%1,'%2','%3','%4',%5,'%6','%7','%8')").arg(info.fileid).arg(info.name).arg(info.dir).arg(info.absolutePath).arg(info.size).arg(info.md5).arg(info.time).arg(info.fileType);
    m_sql->UpdateSql(sqlstr);
}

void CKernel::slot_deleteUploadTask(FileInfo &info)
{
    QString sqlstr = QString("delete from t_upload where f_id=%1 and f_dir='%2';").arg(info.fileid).arg(info.dir);
    m_sql->UpdateSql(sqlstr);
}

void CKernel::slot_deleteDownloadTask(FileInfo &info)
{
    QString sqlstr = QString("delete from t_download where f_id=%1 and f_dir='%2' and f_absolutePath='%3';").arg(info.fileid).arg(info.dir).arg(info.absolutePath);
    m_sql->UpdateSql(sqlstr);
}

void CKernel::slot_getUploadTask(QList<FileInfo> &lstInfo)
{
    QString sqlstr = QString("select * from t_upload;");
    QStringList lst;
    m_sql->SelectSql(sqlstr, 8, lst);
    while(lst.size() != 0){
        FileInfo info;
        info.fileid = lst.front().toInt(); lst.pop_front();
        info.name = lst.front(); lst.pop_front();
        info.dir = lst.front(); lst.pop_front();
        info.absolutePath = lst.front(); lst.pop_front();
        info.size = lst.front().toInt(); lst.pop_front();
        info.md5 = lst.front(); lst.pop_front();
        info.time = lst.front(); lst.pop_front();
        info.fileType = lst.front(); lst.pop_front();
        lstInfo.push_back(info);
    }
}

void CKernel::slot_getDownloadTask(QList<FileInfo> &lstInfo)
{
    QString sqlstr = QString("select * from t_download;");
    QStringList lst;
    m_sql->SelectSql(sqlstr, 8, lst);
    while(lst.size() != 0){
        FileInfo info;
        info.fileid = lst.front().toInt(); lst.pop_front();
        info.name = lst.front(); lst.pop_front();
        info.dir = lst.front(); lst.pop_front();
        info.absolutePath = lst.front(); lst.pop_front();
        info.size = lst.front().toInt(); lst.pop_front();
        info.md5 = lst.front(); lst.pop_front();
        info.time = lst.front(); lst.pop_front();
        info.fileType = lst.front(); lst.pop_front();
        lstInfo.push_back(info);
    }
}

void CKernel::SendData(char *buf, int nlen)
{
    m_tcpClient->SendData(0, buf, nlen);
}

void CKernel::updateFileList()
{
    //删除当前页面文件列表
    m_mainDialog->deleteFileList();
    STRU_FILE_LIST_RQ rq;
    rq.userid = m_id;
    std::string curDir = m_curPath.toStdString();
    strcpy(rq.dir, curDir.c_str());
    SendData((char*)&rq, sizeof(rq));
}
