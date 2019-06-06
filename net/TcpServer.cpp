#include"TcpServer.h"

TcpServer::TcpServer(const IPAddress &listenAddr)
    :listenAddr_(listenAddr_),
    loop_(std::make_shared<EventLoop>())
{   
    listenfd_ = ::socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, IPPROTO_TCP);
    if(listenfd_ == -1){
        perror("TcpServer(const IPAddress &listenAddr)");
        return;
    }
    auto addr_in = listenAddr.addr_in();
     int ret = ::bind(listenfd_, (sockaddr*)&addr_in, sizeof(sockaddr_in));
    if(ret == -1){
        perror("TcpServer(const IPAddress &listenAddr)");
        exit(1);
    }
}

void TcpServer::run(){
    int ret = ::listen(listenfd_, 100);
    if(ret == -1){
        perror("TcpServer::run()");
        return;
    }

    while(running_){
        int clientfd = ::accept4(listenfd_, NULL, NULL, SOCK_NONBLOCK);
        if(clientfd == -1)
            continue;
        TcpConnectionPtr conn = std::make_shared<TcpConnection>(clientfd, loop_);
        conections.push_back(conn);
    }
}