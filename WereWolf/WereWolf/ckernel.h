#ifndef CKERNEL_H
#define CKERNEL_H

#include <QObject>
#include "TcpClientMediator.h"
#include "UdpMediator.h"
#include "logindialog.h"
#include "gameroomdialog.h"
#include "maindialog.h"
#include "packdef.h"
#include <iostream>
#include "friendlist.h"
#include "frienditem.h"
#include "chatdlg.h"
#include "createroom.h"
#include "addroom.h"
#include "audio_read.h"
#include "audio_write.h"
#include "roomlist.h"

#include<winsock2.h>
#include<ws2tcpip.h>
#include<process.h>

using namespace std;

//类函数指针类型
class CKernel;
typedef void (CKernel::*PFUN)( unsigned int lSendIP , char* buf , int nlen );

class CKernel : public QObject
{
    Q_OBJECT
public:
    explicit CKernel(QObject *parent = nullptr);
    static CKernel* getInstance(){
        static CKernel kernel;
        return &kernel;
    }

signals:

public slots:
    //创建房间
    void slot_createRoomInfo(int num, bool hasPwd, QString pwd);
    //加入房间
    void slot_addRoomInfo(QString roomID, QString pwd);
private slots:
    //页面交互
    //登录界面
    void slot_loginInfo(QString tel, QString pwd);
    void slot_registerInfo(QString tel, QString pwd, QString name);

    //主界面
    //获取好友列表
    void slot_clickFirendList();
    //创建房间
    void slot_createRoom();
    //加入房间
    void slot_addRoom();
    //房间列表
    void slot_getRoomList(int num);

    //好友列表界面
    //搜索某人信息
    void slot_searchOne(QString tel);

    //名片控件
    //添加好友
    void slot_addFriend(int userid);
    //聊天
    void slot_chatWithOne(int id, QString name);

    //聊天界面
    void slot_SendChatMsg(int id, QString content);


    //游戏界面
    void slot_leaveRoom(std::string roomID, int pos);
    void slot_sendRoomChatMsg(std::string roomID, int pos, QString content);
    void slot_readGame(int pos, std::string roomID);
    void slot_cancelReadGame(int pos, std::string roomID);
    //回合控制
    void slot_nightOver(int roomID, int roleType, int id);
    void slot_dayOver(int roomID, int roleType, int id);
    void slot_overRound(int roomID, int pos);


    void slot_dealReadyData(uint lSendIP, char* buf, int len);
    //接收网络包处理
    void slot_dealLoginRs(uint lSendIP, char* buf, int len);
    void slot_dealRegissterRs(uint lSendIP, char* buf, int len);
    //好友列表返回
    void slot_dealFriendInfoList(uint lSendIP, char* buf, int len);
    //搜索返回
    void slot_dealSearchRs(uint lSendIP, char* buf, int len);
    //好友申请
    void slot_dealAddFriendRq(uint lSendIP, char* buf, int len);
    void slot_dealAddFriendRs(uint lSendIP, char* buf, int len);
    //聊天包
    void slot_dealChatPack(uint lSendIP, char* buf, int len);
    //创建房间回复
    void slot_dealCreateRoomRs(uint lSendIP, char* buf, int len);
    //加入房间回复
    void slot_dealAddRoomRs(uint lSendIP, char* buf, int len);
    //离开房间回复
    void slot_dealLeaveRoomRs(uint lSendIP, char* buf, int len);
    //获取房间列表
    void slot_dealRoomListRs(uint lSendIP, char* buf, int len);
    //房间包
    void slot_dealRoomChat(uint lSendIP, char* buf, int len);
    //开始游戏
    void slot_dealStartGame(uint lSendIP, char* buf, int len);
    //分发角色
    void slot_dealRole(uint lSendIP, char* buf, int len);
    //回合
    void slot_dealRoundPack(uint lSendIP, char* buf, int len);
    //结果返回包 谁死了 死因
    void slot_dealResult(uint lSendIP, char* buf, int len);
    //预言家专属 身份包
    void slot_dealIdentity(uint lSendIP, char* buf, int len);
    //游戏结束
    void slot_dealGameOver(uint lSendIP, char* buf, int len);
    //狼人阵营 狼人专属
    void slot_dealAllWolf(uint lSendIP, char* buf, int len);

    //udp群聊
    void slot_dealRoomChatUdp(uint lSendIP, char* buf, int len);

    //音频
    //发送
    void slot_sendAudioFrame(QByteArray data);
    //接收
    void slot_dealAudioFrame(uint lSendIP, char* buf, int len);
private:
    void SendData(char* buf, int len);
    void setNetMap();
    void setConfig();
private:
    QString m_ip;
    int m_port;
    QString m_name;
    int m_id;
    int m_tx;
    int m_roomID;
    int m_pos;
    int m_role;
    bool isNight;

    TcpClientMediator   *m_tcpClient;
//    int udpSockFd;
//    sockaddr_in
    UdpMediator         *m_udpMediator;

    PFUN m_netMap[_DEF_PROTOCOL_COUNT];

    //界面成员
    LoginDialog *m_loginDlg;
    MainDialog *m_mainDlg;
    GameRoomDialog *m_gameDlg;
    FriendList *m_friendListDlg;
    CreateRoom *m_createRoomDlg;
    AddRoom *m_addRoomDlg;
    RoomList *m_roomListDlg;

    //聊天窗口map
    map<int ,ChatDlg*> m_mapIDtoChatDlg;
    Audio_Read *m_pAudioRead;
    map<int, Audio_Write*> m_mapIDtoAudioItem;

};

#endif // CKERNEL_H
