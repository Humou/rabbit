#include"Socket.h"

#include<unistd.h>

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

void Socket::read_n(void *buf, size_t count){
    size_t rw = 0;
    while(rw < count){
        int rt = ::read(fd_, buf + rw, count - rw);
        if(rt == -1){
            perror("Socket::read_n");
            exit(1);
        }

        rw += rt;
    }
}

 int Socket::tcpSocket(){
     int fd_ = ::socket(AF_INET, SOCK_STREAM, 0);
    if(fd_ == -1){
        perror("Socket::Socket");
        exit(1);
    }
 }