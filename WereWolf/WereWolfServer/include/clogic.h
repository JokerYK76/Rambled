#ifndef CLOGIC_H
#define CLOGIC_H

#include "TCPKernel.h"
#include <list>
#include "UdpSocket.h"

//roomID——映射——房间属性
struct RoomInfo{
    RoomInfo(): maxNum(0), curNum(0), hasPwd(false), readyNum(0), aliveWolfCount(0), aliveCivilianCount(0), aliveGoldCount(0), wolfKill(0), poisonKill(0), isDied(0), lastGuard(0), isStop(false), curGuard(0), isOver(true), hadProphet(false), killCount(0){
        memset(seatState, 0, sizeof(seatState));
        memset(pwd, 0, sizeof(pwd));
        memset(tx, 0, sizeof(tx));
        memset(readyState, 0, sizeof(readyState));
        memset(roleState, 0, sizeof(roleState));
        memset(seatAlive, 0, sizeof(seatAlive));
        memset(seatVote, 0, sizeof(seatVote));
    }
    int maxNum;//最大人数
    int curNum;//当前人数
    int tx[_MAX_SIZE];
    bool seatState[12];//座位情况
    bool hasPwd;//有无密码
    char pwd[_MAX_SIZE];//密码
    sock_fd seatFd[12];//套接字
    string seatIP[12];
    uint16_t seatPort[12];
    int readyState[_MAX_SIZE];
    int readyNum;

    //游戏开始 身份计数
    int roleState[_MAX_SIZE];//身份
    int aliveWolfCount; //存活狼人数量
    int aliveCivilianCount; //存活平民数量
    int aliveGoldCount; //存活神职数量
    //杀死目标, 守护目标 ，治疗目标
    int wolfKill;
    int killCount;
    int poisonKill;//不可守护，必死
    bool isDied;//只负责狼人杀的标志 双奶 会死
    int lastGuard;//上次守护的人
    int curGuard;
    int seatAlive[12];
    int seatVote[12];

    bool hadProphet;
    //结束发言标志
    bool isStop;
    int curRoundOne;
    //游戏结束
    bool isOver;

};




class CLogic
{
public:
    CLogic( TcpKernel* pkernel )
    {
        m_pKernel = pkernel;
        m_sql = pkernel->m_sql;
        m_tcp = pkernel->m_tcp;
        m_udpSock = new UdpSocket;

        m_udpSock->Socket();
        m_udpSock->Bind(_DEF_PORT_UDP);
        int err;
        pthread_t tid;
        if((err = pthread_create(&tid,NULL, UdpCustom,(void*)this))>0)
        {
            printf("create udpThread error:%s\n",strerror(err));
            return;
        }
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
    //获取好友列表
    void GetFriendList(sock_fd clientfd, char*szbuf, int nlen);
    //获取名片信息
    void GetOneInfo(sock_fd clientfd, char*szbuf, int nlen);
    //好友申请
    void AddFriendRq(sock_fd clientfd, char*szbuf, int nlen);
    void AddFriendRs(sock_fd clientfd, char*szbuf, int nlen);
    //聊天
    void SendMsg(sock_fd clientfd, char*szbuf, int nlen);
    //创建房间
    void CreateRoom(sock_fd clientfd, char* szbuf, int len);
    //加入房间
    void AddRoom(sock_fd clientfd, char* szbuf, int len);
    //离开房间
    void LeaveRoom(sock_fd clientfd, char* szbuf, int len);
    //房间聊天
    void RoomChat(sock_fd clientfd, char* szbuf, int len);
    //准备
    void ReadyGame(sock_fd clientfd, char* szbuf, int len);
    //取消准备
    void CancelReadyGame(sock_fd clientfd, char* szbuf, int len);
    //角色行为
    void RoleBehavior(sock_fd clientfd, char* szbuf, int len);
    //投票
    void VoteBehavior(sock_fd clientfd, char* szbuf, int len);
    //结束发言
    void OverSpeakRound(sock_fd clientfd, char* szbuf, int len);
    //语音
    void ForwardAudio(sock_fd clientfd, char* szbuf, int len);
    //房间列表
    void RoomListRq(sock_fd clientfd, char* szbuf, int len);

    /************** 游戏控制 *********************/
    //游戏
    void ControlGame(RoomInfo* room);
    //角色分配
    void AllocateRoles(RoomInfo* room);
    //群发
    void SendToAll(RoomInfo* room, STRU_ROUND pack);
    void SendToAll(RoomInfo* room, STRU_ROLE pack);
    void SendToAll(RoomInfo* room, STRU_ANSWER pack);
    void SendToAll(RoomInfo* room, STRU_GAME_END pack);

    //线程
    static void *UdpCustom( void* arg);

    UdpSocket *udpSock() const;

    MyMap<int, RoomInfo *> mapRoomIDtoRoom() const;

private:
    TcpKernel* m_pKernel;
    UdpSocket *m_udpSock;
    CMysql * m_sql;
    Block_Epoll_Net * m_tcp;
    MyMap<int, UserInfo*> m_mapIdToUserInfo;
    MyMap<int, RoomInfo*> m_mapRoomIDtoRoom;
    MyMap<int, list<int>*> m_roomList;
};



#endif // CLOGIC_H
