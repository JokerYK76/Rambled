#ifndef CLOGIC_H
#define CLOGIC_H

#include"TCPKernel.h"

class CLogic
{
public:
    CLogic( TcpKernel* pkernel )
    {
        m_pKernel = pkernel;
        m_sql = pkernel->m_sql;
        m_tcp = pkernel->m_tcp;
    }
public:
    //设置协议映射
    void setNetPackMap();
    /************** 发送数据*********************/
    void SendData( sock_fd clientfd, char*szbuf, int nlen )
    {
        m_pKernel->SendData( clientfd ,szbuf , nlen );
    }
    /************** 网络处理 *********************/
    //注册
    void RegisterRq(sock_fd clientfd, char*szbuf, int nlen);
    //登录
    void LoginRq(sock_fd clientfd, char*szbuf, int nlen);
    //获取文件列表请求
    void UserFileListRq(sock_fd clientfd, char*szbuf, int nlen);
    //下载请求处理
    void DownloadFileRq(sock_fd clientfd, char*szbuf, int nlen);
    void DownloadFileRs(sock_fd clientfd, char*szbuf, int nlen);
    void FileContentRs(sock_fd clientfd, char*szbuf, int nlen);
    //上传请求处理
    void UploadFileRq(sock_fd clientfd, char*szbuf, int nlen);
    //上传文件内容请求
    void FileContentRq(sock_fd clientfd, char*szbuf, int nlen);
    //新建文件夹请求
    void AddFolderRq(sock_fd clientfd, char*szbuf, int nlen);
    //删除文件请求
    void DeleteFileRq(sock_fd clientfd, char*szbuf, int nlen);
    //分享文件请求
    void ShareFileRq(sock_fd clientfd, char*szbuf, int nlen);
    //共享列表请求
    void MyShareRq(sock_fd clientfd, char*szbuf, int nlen);
    //获取共享请求
    void GetShareRq(sock_fd clientfd, char*szbuf, int nlen);
    //下载续传
    void ContinueDownload(sock_fd clientfd, char*szbuf, int nlen);
    //上传位置
    void GetUploadPosRq(sock_fd clientfd, char*szbuf, int nlen);
    /*******************************************/
    //下载文件
    void DownLoadFile(int clientfd, int userid, list<string>& lst);
    //下载文件夹
    void DownLoadFolder(int clientfd, int userid, int fileid, string name,string dir);
    //分享单个
    void ShareItem(int userId, int fileId, string dir, string time, int link);
    //分享文件
    void ShareFile(int userId, int fileId, string dir, string time, int link);
    //分享文件夹
    void ShareFolder(int userId, int fileId, string dir, string time, int link, string name);

    void DeleteItem(int userId, int fileId, string dir);
    void DeleteFile(int userId, int fileId, string name, int count, string path, string dir);
    void DeleteFolder(int userId, int fileId, string name, int count, string path, string dir);
    void GetShareByFile(int userId, int fileId, string path);
    void GetShareByFolder(int userId, int fileId, string dir, int fromUserId, string fromDir, string name);
private:
    TcpKernel* m_pKernel;
    CMysql * m_sql;
    Block_Epoll_Net * m_tcp;
    MyMap<int,UserInfo*> m_mapIdToUserInfo;
    MyMap<string, FileInfo*> m_mapFileidtoFileInfo;//key(string)：userid + fileid，多个人下载同一个文件
};

#endif // CLOGIC_H
