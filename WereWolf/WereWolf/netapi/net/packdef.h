#pragma once

#include "memory.h"
#include <iostream>

//默认网络参数
#define _DEFAULT_IP "192.168.1.93"
#define _DEFAULT_PORT       8004
#define _DEFAULT_PORT_UDP   8080

#define _DEF_BUFFER  ( 4096 )
#define _DEF_CONTENT_SIZE	(1024)
#define _MAX_SIZE	(40)
#define _MAX_PATH_SIZE  (260)

//自定义协议   先写协议头 再写协议结构
//登录 注册 获取好友信息 添加好友 聊天 发文件 下线请求
#define _DEF_PROTOCOL_BASE	(10000)
#define _DEF_PROTOCOL_COUNT (100)

//注册
#define _DEF_PACK_REGISTER_RQ	(_DEF_PROTOCOL_BASE + 0 )
#define _DEF_PACK_REGISTER_RS	(_DEF_PROTOCOL_BASE + 1 )
//登录
#define _DEF_PACK_LOGIN_RQ	(_DEF_PROTOCOL_BASE + 2 )
#define _DEF_PACK_LOGIN_RS	(_DEF_PROTOCOL_BASE + 3 )

#define MAX_FRIEND_NUMS 100
#define MAX_ROOM_NUM    50

//返回的结果
//注册请求的结果
#define tel_is_exist		(0)
#define name_is_exist		(1)
#define register_success	(2)
//登录请求的结果
#define user_not_exist		(0)
#define password_error		(1)
#define login_success		(2)

//回合时间控制
#define _DEF_TIME_NIGHT     15
#define _DEF_TIME_DAY       60
#define _DEF_TIME_VOTE      15

typedef int PackType;

//协议结构
//注册
typedef struct STRU_REGISTER_RQ
{
	STRU_REGISTER_RQ():type(_DEF_PACK_REGISTER_RQ)
	{
		memset( tel  , 0, sizeof(tel));
		memset( name  , 0, sizeof(name));
		memset( password , 0, sizeof(password) );
	}
	//需要手机号码 , 密码, 昵称
	PackType type;
	char tel[_MAX_SIZE];
	char name[_MAX_SIZE];
	char password[_MAX_SIZE];

}STRU_REGISTER_RQ;

typedef struct STRU_REGISTER_RS
{
	//回复结果
	STRU_REGISTER_RS(): type(_DEF_PACK_REGISTER_RS) , result(register_success)
	{

	}
	PackType type;
	int result;

}STRU_REGISTER_RS;

//登录
typedef struct STRU_LOGIN_RQ
{
	//登录需要: 手机号 密码 
	STRU_LOGIN_RQ():type(_DEF_PACK_LOGIN_RQ)
	{
		memset( tel , 0, sizeof(tel) );
		memset( password , 0, sizeof(password) );
	}
	PackType type;
	char tel[_MAX_SIZE];
	char password[_MAX_SIZE];

}STRU_LOGIN_RQ;

typedef struct STRU_LOGIN_RS
{
    // 需要 结果 , 用户的id
    STRU_LOGIN_RS(): type(_DEF_PACK_LOGIN_RS) , result(login_success),userid(0), u_tx(0)
    {
        memset( name  , 0, sizeof(name));
        memset( label  , 0, sizeof(label));
    }
    PackType type;
    int result;
    int userid;
    int u_tx;
    char name[_MAX_SIZE];
    char label[_MAX_SIZE];

}STRU_LOGIN_RS;

//请求好友列表
#define _DEF_PACK_FRIENDS_RQ (_DEF_PROTOCOL_BASE + 4)
struct STRU_FRIEND_RQ
{
    STRU_FRIEND_RQ(): type(_DEF_PACK_FRIENDS_RQ), uid(0){

    }
    PackType type;
    int uid;
};
//好友信息
struct FriendInfo{
    char name[_MAX_SIZE];
    char label[_MAX_SIZE];
    int userid;
    int tx;
};

//好友列表
#define _DEF_PACK_FRIENDS_RS (_DEF_PROTOCOL_BASE + 5)
struct STRU_FRIENDINFO_LIST{
    STRU_FRIENDINFO_LIST(): type(_DEF_PACK_FRIENDS_RS), uid(0), nums(0){
        memset(friends, 0, sizeof(FriendInfo)*MAX_FRIEND_NUMS);
    }
    PackType type;
    int uid;
    int nums;
    FriendInfo friends[MAX_FRIEND_NUMS];
};

//查询包结构体
#define _DEF_PACK_SEARCH_RQ (_DEF_PROTOCOL_BASE + 6)
struct STRU_SEARCH_RQ
{
    STRU_SEARCH_RQ() :type(_DEF_PACK_SEARCH_RQ), myID(0){
        memset(tel, 0, 12);
    }
    PackType type;
    int myID;
    char tel[12];
};
//返回查询结果包
#define _DEF_PACK_SEARCH_RS (_DEF_PROTOCOL_BASE + 7)

#define _SEARCH_KIND_FRIEND     0
#define _SEARCH_KIND_NOSHIP     1
#define _SEARCH_KIND_ISME       2
#define _SEARCH_KIND_NO_EXIST   3

//查询结果返回包
struct STRU_SEARCH_RS
{
    STRU_SEARCH_RS() :type(_DEF_PACK_SEARCH_RS), hisID(0), relationship(_SEARCH_KIND_FRIEND){
        memset(&hisInfo, 0, sizeof(hisInfo));
    }
    PackType type;
    int hisID;
    int relationship;
    FriendInfo hisInfo;
};

//添加好友请求
#define _DEF_PACK_ADD_FRIEND_RQ (_DEF_PROTOCOL_BASE + 8)
struct STRU_ADD_FRIEND_RQ{
    STRU_ADD_FRIEND_RQ(): type(_DEF_PACK_ADD_FRIEND_RQ), userID(0), hisID(0){

    }
    PackType type;
    int userID;//主动方
    int hisID;//被动方
};
#define _DEF_PACK_ADD_FRIEND_RS (_DEF_PROTOCOL_BASE + 9)

#define _ADD_RESULT_REFUSE  0
#define _ADD_RESULT_AGREE   1

struct STRU_ADD_FRIEND_RS{
    STRU_ADD_FRIEND_RS(): type(_DEF_PACK_ADD_FRIEND_RS), userID(0), hisID(0), result(_ADD_RESULT_AGREE){
    }
    PackType type;
    int userID;//主动方
    int hisID;//被动方
    int result;
};

#define _DEF_PACK_CHAT (_DEF_PROTOCOL_BASE + 10)
struct STRU_CHAT
{
    STRU_CHAT() : type(_DEF_PACK_CHAT), userID(0), hisID(0){
        memset(content, 0, sizeof(content));
        memset(myName, 0, sizeof(myName));
    }
    PackType type;
    int userID;
    int hisID;
    char myName[_MAX_SIZE];
    char content[_DEF_CONTENT_SIZE];
};

//创建房间请求
#define _DEF_PACK_CREATE_ROOM_RQ (_DEF_PROTOCOL_BASE + 11)
struct STRU_CREATE_ROOM_RQ
{
    STRU_CREATE_ROOM_RQ(): type(_DEF_PACK_CREATE_ROOM_RQ), userID(0), tx(0), num(0), hasPWD(false){
        memset(pwd, 0, sizeof(pwd));
    }
    PackType type;
    int userID;
    int tx;
    int num;//人数
    bool hasPWD;
    char pwd[_MAX_SIZE];
};

//创建房间回复
#define _DEF_PACK_CREATE_ROOM_RS (_DEF_PROTOCOL_BASE + 12)

#define _CREATE_ROOM_FAILED      1
#define _CREATE_ROOM_SUCCESS     0

struct STRU_CREATE_ROOM_RS
{
    STRU_CREATE_ROOM_RS(): type(_DEF_PACK_CREATE_ROOM_RS), userID(0), num(0), result(_CREATE_ROOM_SUCCESS){
        memset(roomID, 0, sizeof(roomID));
        memset(pwd, 0, sizeof(pwd));
    }
    PackType type;
    int userID;
    int num;//生成界面
    int result;
    char roomID[_MAX_SIZE];
    char pwd[_MAX_SIZE];
};

//加入房间请求
#define _DEF_PACK_ADD_ROOM_RQ (_DEF_PROTOCOL_BASE + 13)
struct STRU_ADD_ROOM_RQ
{
    STRU_ADD_ROOM_RQ(): type(_DEF_PACK_ADD_ROOM_RQ), userID(0), tx(0){
        memset(pwd, 0, sizeof(pwd));
        memset(roomID, 0, sizeof(roomID));
    }
    PackType type;
    int userID;
    int tx; //其他人更新
    char roomID[_MAX_SIZE];
    char pwd[_MAX_SIZE];
};

//加入房间回复
#define _DEF_PACK_ADD_ROOM_RS (_DEF_PROTOCOL_BASE + 14)

#define _ADD_ROOM_SUCCESS       0
#define _ADD_ROOM_FAILED_NOROOM 1
#define _ADD_ROOM_FAILED_FULL   2
#define _ADD_ROOM_FAILED_PWDERR 3

struct STRU_ADD_ROOM_RS
{
    STRU_ADD_ROOM_RS(): type(_DEF_PACK_ADD_ROOM_RS), userID(0), pos(0), num(0), tx(0), result(_ADD_ROOM_SUCCESS){
        memset(roomID, 0, sizeof(roomID));
        memset(pwd, 0, sizeof(pwd));
    }
    PackType type;
    int userID;
    int pos;
    int num;
    int tx;
    int result;
    char pwd[_MAX_SIZE];
    char roomID[_MAX_SIZE];
};

//离开房间
#define _DEF_PACK_LEAVE_ROOM (_DEF_PROTOCOL_BASE + 15)
struct STRU_LEAVE_ROOM
{
    STRU_LEAVE_ROOM() : type(_DEF_PACK_LEAVE_ROOM), userID(0), pos(0){
        memset(roomID, 0, sizeof(roomID));
    }
    PackType type;
    int userID;
    char roomID[_MAX_SIZE];
    int pos;
};

//离开房间通知
#define _DEF_PACK_LEAVE_ROOM_RS (_DEF_PROTOCOL_BASE + 16)
struct STRU_LEAVE_ROOM_RS
{
    STRU_LEAVE_ROOM_RS() : type(_DEF_PACK_LEAVE_ROOM_RS), pos(0){
    }
    PackType type;
    int pos;
};

//房间内聊天
#define _DEF_PACK_ROOM_CHAT (_DEF_PROTOCOL_BASE + 17)
struct STRU_ROOM_CHAT
{
    STRU_ROOM_CHAT() : type(_DEF_PACK_ROOM_CHAT), pos(0){
        memset(roomID, 0, sizeof(roomID));
    }
    PackType type;
    char roomID[_MAX_SIZE];
    int pos;
    char content[_DEF_CONTENT_SIZE];
};

//准备
#define _DEF_PACK_READY (_DEF_PROTOCOL_BASE + 18)
struct STRU_READY
{
    STRU_READY() : type(_DEF_PACK_READY), pos(0){
    }
    PackType type;
    char roomID[_MAX_SIZE];
    int pos;
};

//取消准备
#define _DEF_PACK_CANCEL_READY (_DEF_PROTOCOL_BASE + 19)
struct STRU_CANCEL_READY
{
    STRU_CANCEL_READY() : type(_DEF_PACK_CANCEL_READY), pos(0){
    }
    PackType type;
    char roomID[_MAX_SIZE];
    int pos;
};

//开始 服务器发送通知客户端
#define _DEF_PACK_START (_DEF_PROTOCOL_BASE + 20)
struct STRU_START
{
    STRU_START() : type(_DEF_PACK_START){
    }
    PackType type;
};

//角色分配
#define _DEF_PACK_ROLE (_DEF_PROTOCOL_BASE + 21)

#define _ROLE_TYPE_NUMS         7
#define _ROLE_CIVILIAN          1
#define _ROLE_PROPHET           2
#define _ROLE_WITCH             3
#define _ROLE_GUARD             4
#define _ROLE_HUNTER            5
#define _ROLE_WOLF              6
#define _ROLE_WOLF_KING_WHITE   7


struct STRU_ROLE
{
    STRU_ROLE() : type(_DEF_PACK_ROLE), roleType(_ROLE_CIVILIAN){
    }
    PackType type;
    int roleType;
};

//回合包
#define _DEF_PACK_ROUND (_DEF_PROTOCOL_BASE + 22)

#define _ROUND_VOTE     100

struct STRU_ROUND{
    STRU_ROUND(): type(_DEF_PACK_ROUND), roundNum(0), isNight(true), roleBehavior(0){

    }
    PackType type;
    int roundNum;
    bool isNight;//用于区分黑夜白天 环节不同
    int roleBehavior;//职业回合 死亡编号
};
//操作包
#define _DEF_PACK_BEHAVIOR (_DEF_PROTOCOL_BASE + 23)
//女巫两种操作
#define _BEHAVIOR_WITCH_KILL    -1
#define _BEHAVIOR_WITCH_SAVE    -2

struct STRU_BEHAVIOR{
    STRU_BEHAVIOR(): type(_DEF_PACK_BEHAVIOR), roomID(0), roleType(0), who(0){

    }
    PackType type;
    int roomID;
    int roleType;
    int who;
};

//系统返回结果包
#define _DEF_PACK_ANSWER (_DEF_PROTOCOL_BASE + 24)

#define _ANSWER_KILL    1
#define _ANSWER_VOTE    2
struct STRU_ANSWER{
    STRU_ANSWER() : type(_DEF_PACK_ANSWER), who(0), second(0), diedCause(0){

    }
    PackType type;
    int who;
    int second;
    int diedCause;
};

//身份包
#define _DEF_PACK_IDENTITY (_DEF_PROTOCOL_BASE + 25)
struct STRU_IDENTITY{
    STRU_IDENTITY() : type(_DEF_PACK_IDENTITY), id(0), identity(0){

    }
    PackType type;
    int id;
    int identity;
};

//游戏结束
#define _DEF_PACK_GAME_END (_DEF_PROTOCOL_BASE + 26)

#define _WIN_CAMP_GOOD  1
#define _WIN_CAMP_WOLF  2

struct STRU_GAME_END{
    STRU_GAME_END() : type(_DEF_PACK_GAME_END), winCamp(0){

    }
    PackType type;
    int winCamp;
};

//投票
#define _DEF_PACK_VOTEONE (_DEF_PROTOCOL_BASE + 27)
struct STRU_VOTEONE{
    STRU_VOTEONE() : type(_DEF_PACK_VOTEONE), roomID(0), myID(0), hisID(0){

    }
    PackType type;
    int roomID;
    int myID;
    int hisID;
};

//结束发言
#define _DEF_PACK_OVER_ROUND (_DEF_PROTOCOL_BASE + 28)
struct STRU_OVER_ROUND{
    STRU_OVER_ROUND() : type(_DEF_PACK_OVER_ROUND), roomID(0), myID(0){

    }
    PackType type;
    int roomID;
    int myID;
};

//狼人通知
#define _DEF_PACK_ALLWOLF   (_DEF_PROTOCOL_BASE + 29)
struct STRU_ALLWOLF{
    STRU_ALLWOLF(): type(_DEF_PACK_ALLWOLF), wolfNum(0){
        memset(wolfs, 0, sizeof(wolfs));
    }
    PackType type;
    int wolfNum;
    int wolfs[5];
};

//音频包
#define _DEF_PACK_AUDIO (_DEF_PROTOCOL_BASE + 30)
//区分狼交流 和普通发言环节
#define _AUDIO_KIND_WOLF    0
#define _AUDIO_KIND_NORMAL  1

//房间列表包
#define _DEF_PACK_ROOMLIST_RQ   (_DEF_PROTOCOL_BASE + 31)

struct STRU_ROOMLIST_RQ
{
    STRU_ROOMLIST_RQ() : type(_DEF_PACK_ROOMLIST_RQ), roomType(0){}
    PackType type;
    int roomType;
};

//房间列表包
#define _DEF_PACK_ROOMLIST_RS   (_DEF_PROTOCOL_BASE + 32)

struct RoomItemInfo
{
    RoomItemInfo() : roomID(0), curNum(0), maxNum(0), hasPWD(false){}
    int roomID;
    int curNum;
    int maxNum;
    bool hasPWD;
};

struct STRU_ROOMLIST_RS
{
    STRU_ROOMLIST_RS() : type(_DEF_PACK_ROOMLIST_RS), num(0){}
    PackType type;
    int num;
    RoomItemInfo rooms[MAX_ROOM_NUM];
};

//UDP
//添加房间内用户的ip 和 端口 保存
#define _DEF_PACK_ROOMCHAT (_DEF_PROTOCOL_BASE + 33)
struct STRU_ROOMCHAT{
    STRU_ROOMCHAT() : type(_DEF_PACK_ROOMCHAT), roomID(0), myPos(0){
        memset(content, 0, sizeof(content));
    }
    PackType type;
    int roomID;//检索房间信息结构体
    int myPos;//发言人
    char content[_DEF_CONTENT_SIZE];
};

//用于获取udp传输 相关数据
#define _DEF_PACK_UDP_INFO (_DEF_PROTOCOL_BASE + 34)
struct STRU_UDP_INFO
{
    STRU_UDP_INFO() :type(_DEF_PACK_UDP_INFO), userID(0){}
    PackType type;
    int userID;
};
