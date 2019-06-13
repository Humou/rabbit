#include"TcpConnection.h"

#include<memory>
#include<sys/socket.h>
#include<iostream>
TcpConnection::TcpConnection(int fd, EventLoopPtr &eventLoop)
    :loop_(eventLoop),
    fd_(fd),
    bridge_(std::make_shared<Bridge>(fd_, loop_))
{
}
void TcpConnection::setReadCallBack(ReadCallBack cb){
    readCallBack_ = cb;
    bridge_->setReadCallBack(std::bind(&TcpConnection::handleRead, this));
}

void TcpConnection::setWriteCalBack(WriteCallBack cb){
    writeCallBack_ = cb;
    bridge_->setWriteCallBack(std::bind(&TcpConnection::handleWrite, this));
}

 void TcpConnection::handleRead(){
    if(connectionCallBack_){
        connectionCallBack_(shared_from_this());
        return;
    }
     int ret = inputBuffer_.readFd(fd_, nullptr);
     if(ret == -1) {
         return;
     }
     else if(ret == 0){
        return;
     }
    
     if(readCallBack_) readCallBack_(shared_from_this());
 }

 void TcpConnection::handleWrite(){

     if(writeCallBack_) writeCallBack_(shared_from_this());
     int ret = outPutBuffer_.writeFd(fd_, nullptr);
     if(ret == -1){
         return;
     }
     else if(ret == 0){
         //close
     }
 }

 void TcpConnection::handleConnection(){
     if(connectionCallBack_) connectionCallBack_(shared_from_this());
 }
 void TcpConnection::registerToLoop(){
    loop_->addBridge(bridge_);
 }