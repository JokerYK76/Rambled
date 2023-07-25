#include "UdpSocket.h"

bool UdpSocket::Socket()
{
    m_sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (m_sockfd < 0)
    {
        perror("socket error");
        return false;
    }
    return true;
}

bool UdpSocket::Bind(uint16_t port)
{
    //定义IPv4地址结构体
    struct sockaddr_in addr;
    //地址信息赋值
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);//将主机字节序短整型型数据转化为网络字节序数据
    addr.sin_addr.s_addr = INADDR_ANY;//将字符串IP地址转化为网络字节序IP地址
//    addr.sin_addr.s_addr = inet_addr(_DEF_IP_UDP);
    socklen_t len = sizeof(struct sockaddr_in);
    int ret = bind(m_sockfd, (struct sockaddr*)&addr, len);
    if (ret < 0)
    {
        perror("bind error");
        return false;
    }
    return true;
}

bool UdpSocket::Recv(string *buf, string *ip, uint16_t *port)
{
    struct sockaddr_in peer_addr;//用于接收发送端的地址信息
    socklen_t len = sizeof(struct sockaddr_in);
    char tmp[AUDIO_UDP_BUFFER_SIZE] = {0};
    int ret = recvfrom(m_sockfd, tmp, AUDIO_UDP_BUFFER_SIZE, 0, (struct sockaddr*)&peer_addr, &len);
    cout << "接收大小" << ret <<endl;
    if (ret < 0)
    {
        perror("recvfrom error");
        return false;
    }
    buf->assign(tmp, ret);//assign从指定字符串中截取指定长度的数据到buf中
    if (port != NULL)
    {
        *port = ntohs(peer_addr.sin_port);//网络字节序到主机字节序的转换
    }
    if (ip != NULL)
    {
        *ip = inet_ntoa(peer_addr.sin_addr);//网络字节序到字符串IP地址的转换
    }
    return true;
}

bool UdpSocket::Send(char* data, int len, string &ip, const uint16_t port)
{
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr(ip.c_str());
    socklen_t addrLen = sizeof(struct sockaddr_in);
    int ret = sendto(m_sockfd, data, len, 0, (struct sockaddr*)&addr, addrLen);
    if (ret < 0)
    {
        perror("sendto error");
        return false;
    }
    return true;
}

bool UdpSocket::Close()
{
    if (m_sockfd > 0)
    {
        close(m_sockfd);
        m_sockfd = -1;
    }
    return true;
}
