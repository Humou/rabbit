#ifndef SOCKET_H
#define SOCKET_H

#include<sys/types.h>
#include<sys/socket.h>

#include"IPAddress.h"

class Socket{
public:
    Socket(int fd)
    :fd_(fd) {}
    
    //Socket(const IPAddress& ipAddress);
    //Socket();

    void bindOrDie(const IPAddress &ipaddr);
    void listenOrDie(int backlog);
    int acceptOrDie();

    void connectOrDie(const IPAddress &ipaddr);
    void closeOrDie();

    void write_n(void *buf, size_t count);

    int read(void *buf, size_t count);
    int read_n(void *buf, size_t count);
    
static int tcpSocket();
private:
    int fd_ = 0;
};

#endif// SOCK_H