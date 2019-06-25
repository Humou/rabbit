#include"EchoServer.h"
#include"Acceptor.h"
#include"Socket.h"
#include"iostream"
#include"EchoHandler.h"
EchoServer::EchoServer(const IPAddress &listenAddr)
    :loop_(std::make_shared<EventLoop>())
{
    listenfd_ = Socket::createListenFd(listenAddr);
    if(listenfd_ == -1){
        return;
    }
    acceptor_ = std::make_shared<Acceptor<EchoHandler>>(listenfd_, EPOLLIN, loop_);
    acceptor_->registerToLoop();
} 

void EchoServer::run(){
   Socket::listenOrDie(listenfd_,100);
   
    std::cout<<"sever is running"<<std::endl;
    loop_->loop();
}
