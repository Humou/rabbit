#include"Socket.h"

#include<unistd.h>
/* 
 void Socket::bindOrDie(const IPAddress &ipaddr){
     auto addr_in = ipaddr.addr_in();
     int ret = ::bind(fd_, (sockaddr*)&addr_in, sizeof(sockaddr_in));
    if(ret == -1){
        perror("Socket::bindOrDie");
        exit(1);
    }
 }

 void Socket::listenOrDie(int backlog){
     int ret = ::listen(fd_, backlog);
     if(ret == -1){
         perror("Socket::listenOrDie");
         exit(1);
     }
 }

 int Socket::acceptOrDie(){
     int clientfd = ::accept(fd_, NULL, NULL);
     if(clientfd == -1){
         perror("Socket::acceptOrDie");
         exit(1);
     }

     return clientfd;
 }

 void Socket::connectOrDie(const IPAddress &ipaddr){
      auto addr_in = ipaddr.addr_in();
     int ret = ::connect(fd_, (sockaddr*)&addr_in, sizeof(sockaddr_in));
     if(ret == -1){
         perror("Socket::connectOrDie");
         exit(1);
     }
 }

 void Socket::closeOrDie(){
     int ret = ::close(fd_);
    if(ret == -1){
        perror("Socket::closeOrDie");
        exit(1);
    }
 }

void Socket::write_n(void *buf, size_t count){
    size_t written = 0;
    while(written < count){
        int rt = ::write(fd_, buf + written, count - written);
        if(rt == -1){
            perror("Scoket::write_n");
            exit(1);
        }
        written += rt;
    }
}

int Socket::read(void *buf, size_t count){
    size_t rd  = ::read(fd_, buf, count);
    if(rd == -1){
        perror("Socket::read");
        exit(1);
    }

    return rd;
}

int Socket::read_n(void *buf, size_t count){
    size_t rd = 0;
    while(rd < count){
        int rt = ::read(fd_, buf + rd, count - rd);
        if(rt == -1){
            perror("Socket::read_n");
            exit(1);
        }
        else if(rt == 0) return rd;
        rd += rt;
    }

    return rd;
}

 int Socket::tcpSocket(){
     int fd_ = ::socket(AF_INET, SOCK_STREAM, 0);
    if(fd_ == -1){
        perror("Socket::Socket");
        exit(1);
    }
 }
 */
namespace Socket{
    int createListenFd(const IPAddress &listenAddr){
    int listenfd = ::socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, IPPROTO_TCP);
    if(listenfd == -1){
        perror("TcpServer(const IPAddress &listenAddr)");
        return -1;
    }
    
    int on = 1;
    if(::setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, (const void*)&on, sizeof(int)) < 0){
        perror("address");
        return -1;
    }
    if(::setsockopt(listenfd, SOL_SOCKET, SO_REUSEPORT, (const void*)&on, sizeof(int)) < 0){
        perror("port");
        return -1;
    }
    
    auto addr_in = listenAddr.addr_in();
    int ret = ::bind(listenfd, (sockaddr*)&addr_in, sizeof(sockaddr_in));
    if(ret == -1){
        perror("TcpServer(const IPAddress &listenAddr)");
        return -1;
    }

    return listenfd;
    }

    void listenOrDie(int fd_, int backlog){
        int ret = ::listen(fd_, backlog);
        if(ret == -1){
            perror("Socket::listenOrDie");
            exit(1);
     }
    }

    int createClientFd(int listenfd){
        int clientfd = ::accept4(listenfd, NULL, NULL, SOCK_NONBLOCK);
        if(clientfd == -1){
            perror("Socket::createClientFd");
            return -1;
        }

        return clientfd;
    }
}