#include "packdef.h"
#include <cstdio>
#include <string>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>

using namespace std;

#define AUDIO_UDP_BUFFER_SIZE 8192

class UdpSocket
{
public:
    UdpSocket():m_sockfd(-1){}
    //创建套接字
    bool Socket();
    //为套接字绑定地址信息
    bool Bind(uint16_t port);
    //接收数据，获取发送端地址信息
    bool Recv(string *buf, string *ip=NULL, uint16_t *port=NULL);
    //发送数据
    bool Send(char *data, int len, string &ip, const uint16_t port);
    //关闭套接字
    bool Close();
private:
    int m_sockfd;
};

