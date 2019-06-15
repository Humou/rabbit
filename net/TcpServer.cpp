#include"TcpServer.h"

#include<iostream>
TcpServer::TcpServer(const IPAddress &listenAddr)
    :listenAddr_(listenAddr_),
    loop_(std::make_shared<EventLoop>())
{   
    listenfd_ = ::socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, IPPROTO_TCP);
    if(listenfd_ == -1){
        perror("TcpServer(const IPAddress &listenAddr)");
        return;
    }
    
    int on = 1;
    if(::setsockopt(listenfd_, SOL_SOCKET, SO_REUSEADDR, (const void*)&on, sizeof(int)) < 0){
        perror("address");
        return;
    }
    if(::setsockopt(listenfd_, SOL_SOCKET, SO_REUSEPORT, (const void*)&on, sizeof(int)) < 0){
        perror("port");
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
    std::cout<<"sever is running"<<std::endl;

    TcpConnectionPtr conn = std::make_shared<TcpConnection>(listenfd_, loop_);
    //conn->setReadCallBack(std::bind(&TcpServer::readCallBack, this, std::placeholders::_1));
    conn->set_connCallBack(std::bind(&TcpServer::connectionCallback, this, std::placeholders::_1));
    conn->registerToLoop();
    loop_->loop();
}

 void TcpServer::readCallBack(std::shared_ptr<TcpConnection> conn){
     auto message = conn->readAllAsString();
     if(!message.empty())std::cout<<"receive:"<<message;
     conn->writeString("hi client: " + message);
 }

 void TcpServer::writeCallBack(std::shared_ptr<TcpConnection> conn){

 }

 void TcpServer::connectionCallback(std::shared_ptr<TcpConnection> listenConn){
    int clientfd = ::accept4(listenfd_, NULL, NULL, SOCK_NONBLOCK);
    if(clientfd == -1) return;
    TcpConnectionPtr conn = std::make_shared<TcpConnection>(clientfd, loop_);
    conn->set_readCallBack(std::bind(&TcpServer::readCallBack, this, std::placeholders::_1));
    conn->registerToLoop();
    conections.push_back(conn);
 }