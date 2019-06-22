#include"HttpAcceptor.h"
#include"../../http/HttpHandler.h"
#include"../../base/Socket.h"

#include<iostream>
HttpAcceptor::HttpAcceptor(int fd, uint32_t events, std::shared_ptr<EventLoop> &loop)
    :EventHandler(fd, events, loop)
{

}

 void HttpAcceptor::handleRead(){
    int clientfd = Socket::createClientFd(fd_);
    //int clientfd = ::accept4(fd_, NULL, NULL, SOCK_NONBLOCK);
    //EPOLLIN | EPOLLOUT|EPOLLRDHUP
    auto httpHandler = std::make_shared<HttpHandler>(clientfd, EPOLLIN | EPOLLOUT | EPOLLRDHUP, loop_);
    httpHandler->registerToLoop();
 }