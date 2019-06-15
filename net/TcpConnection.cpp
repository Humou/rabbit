#include"TcpConnection.h"

#include<memory>
#include<sys/socket.h>
#include<iostream>
TcpConnection::TcpConnection(int fd, EventLoopPtr &eventLoop)
    :loop_(eventLoop),
    fd_(fd),
    bridge_(std::make_shared<Bridge>(fd_, loop_))
{
    bridge_->set_handleRead(std::bind(&TcpConnection::handleRead, this));
    bridge_->set_handleWrite(std::bind(&TcpConnection::handleWrite, this));
    bridge_->set_handleDisConn(std::bind(&TcpConnection::handleDisConn, this));
    bridge_->set_handleError(std::bind(&TcpConnection::handleError, this));
}

 void TcpConnection::handleRead(){
    if(connCallBack_){
        connCallBack_(shared_from_this());
        return;
    }

    int ret = inputBuffer_.readFd(fd_, nullptr);
    if(readCallBack_) readCallBack_(shared_from_this());
 }

 void TcpConnection::handleWrite(){

    if(writeCallBack_) writeCallBack_(shared_from_this());
    int ret = outPutBuffer_.writeFd(fd_, nullptr);
}

void TcpConnection::handleError(){
    if(errorCallBack_) errorCallBack_(shared_from_this());
}

void TcpConnection::handleDisConn(){
    if(outPutBuffer_.readableBytes() > 0) return;
    ::close(fd_);
}

 void TcpConnection::registerToLoop(){
    loop_->addBridge(bridge_);
 }