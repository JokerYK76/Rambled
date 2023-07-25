#ifndef CKERNEL_H
#define CKERNEL_H

#include <QObject>
#include <map>
#include "maindialog.h"
#include "packdef.h"
#include "logindialog.h"
#include "csqlite.h"

class INetMediator;

//类函数指针类型
class CKernel;
typedef void (CKernel::*PFUN)( unsigned int lSendIP , char* buf , int nlen );

//单例 1.私有化 构造拷贝构造析构函数 2.提供静态的公有获取对象的方法
class CKernel : public QObject
{
    Q_OBJECT
private:
    explicit CKernel(QObject *parent = nullptr);
    /*explicit 防止隐式类型转换 莫名其妙的创建一个对象*/
    ~CKernel(){}
    CKernel(const CKernel &kernel);
public:
    static CKernel* getInstance(){
        static CKernel kernel;
        return &kernel;
    }
    void setConfig();
    void setNetMap();
signals:
    void SIG_updateFileProgress(int fileid, int pos);
    void SIG_updateUploadFileProgress(int fileid, int pos);
private slots:
    void slot_destroyInstance();
    void slot_clientReadyData( unsigned int lSendIP , char* buf , int nlen );
    void slot_serverReadyData( unsigned int lSendIP , char* buf , int nlen );

    void slot_dealRegistRs( unsigned int lSendIP , char* buf , int nlen );
    void slot_dealLoginRs( unsigned int lSendIP , char* buf , int nlen );
    void slot_dealFileInfo( unsigned int lSendIP , char* buf , int nlen );
    //处理下载文件头请求
    void slot_dealFileHeadRq( unsigned int lSendIP , char* buf , int nlen );
    //处理下载文件夹请求
    void slot_dealFolderDownLoadRq(unsigned int lSendIP , char* buf , int nlen );
    //处理下载文件内容
    void slot_dealFileContentRq( unsigned int lSendIP , char* buf , int nlen );
    //处理上传文件头回复
    void slot_dealUploadFileHeadRs( unsigned int lSendIP , char* buf , int nlen );
    //处理上传文件内容回复
    void slot_dealFileContentRs( unsigned int lSendIP , char* buf , int nlen );
    //处理新建文件夹回复
    void slot_dealAddFolderRs( unsigned int lSendIP , char* buf , int nlen );
    void slot_dealQuickUploadFileRs( unsigned int lSendIP , char* buf , int nlen );
    void slot_dealDeleteFileRs( unsigned int lSendIP , char* buf , int nlen );
    void slot_dealShareFileRs( unsigned int lSendIP , char* buf , int nlen );
    void slot_dealMyShareRs( unsigned int lSendIP , char* buf , int nlen );
    void slot_dealGetShareRs( unsigned int lSendIP , char* buf , int nlen );
    //处理上传进度回复
    void slot_dealGetUploadPosRs( unsigned int lSendIP , char* buf , int nlen );

    void slot_uploadFile(QString path);
    void slot_uploadFile(QString path, QString dir);
    void slot_uploadFolder(QString path);
    void slot_uploadFolder(QString path, QString dir);

    void slot_registerCommit( QString tel, QString pwd, QString name );

    void slot_loginCommit( QString tel, QString pwd );
    void slot_downloadFile(int fileid);
    //新建文件夹
    void slot_addFolder( QString name );
    void slot_addFolder(QString name, QString dir);
    //改变路径 以及发送新列表请求
    void slot_changePath( QString path );
    void slot_deleteFile(QString path, QVector<int> fileidArray);
    void slot_shareFile(QString path, QVector<int> fileidArray);
    void slot_refreshMyShare();
    void slot_getShare(QString path, int link);

    void slot_setUploadPause(int fileId, int pauseFlag);
    void slot_setDownloadPause(int fileId, int pauseFlag);



    //本地数据库
    void initDatabase(int id);
    //数据写入
    void slot_writeUploadTask(FileInfo& info);
    void slot_writeDownloadTask(FileInfo& info);
    //数据删除
    void slot_deleteUploadTask(FileInfo& info);
    void slot_deleteDownloadTask(FileInfo& info);
    //数据获取
    void slot_getUploadTask(QList<FileInfo>& lstInfo);
    void slot_getDownloadTask(QList<FileInfo>& lstInfo);
private:
    void SendData( char* buf , int nlen );
    void updateFileList();
private:
    //ui类
    MainDialog* m_mainDialog;
    LoginDialog* m_loginDialog;
    QString m_ip;
    int m_port;
    QString m_name;
    int m_id;
    bool m_quick;

    //INetMediator* m_tcpServer;
    INetMediator* m_tcpClient;
    PFUN m_netPackMap[_DEF_PROTOCOL_COUNT];
    std::map<int, FileInfo> m_mapFileidToFileInfo;
    std::map<std::string, FileInfo> m_mapMD5ToFileInfo;
    QString m_curPath;
    QString m_sysPath;
    CSqlite* m_sql;

};

#endif // CKERNEL_H
