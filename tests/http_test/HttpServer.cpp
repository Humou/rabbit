#include"HttpAcceptor.h"
#include"HttpServer.h"
#include"../../base/Socket.h"
HttpServer::HttpServer(const IPAddress &listenAddr)
 :loop_(std::make_shared<EventLoop>())
{
    listenfd_ = Socket::createListenFd(listenAddr);
    if(listenfd_ == -1) {
        perror("HttpServer::HttpServer(const IPAddress &listenAddr)");
        return;
    }

    acceptor_ = std::make_shared<HttpAcceptor>(listenfd_, EPOLLIN, loop_);
    acceptor_->registerToLoop();
}

void HttpServer::run(){
    Socket::listenOrDie(listenfd_, 100);
    loop_->loop();
}
