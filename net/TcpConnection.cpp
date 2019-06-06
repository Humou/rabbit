#include"TcpConnection.h"

TcpConnection::TcpConnection(int fd, EventLoopPtr &eventLoop)
    :loop_(eventLoop),
    fd_(fd),
    bridge_(std::make_shared<Bridge>(fd_, loop_))
{
    bridge_->setReadCallBack(std::bind(&TcpConnection::handleRead, this));
    bridge_->setWriteCallBack(std::bind(&TcpConnection::handleWrite, this));
    loop_->addBridge(bridge_);
}

 void TcpConnection::handleRead(){
     int ret = inputBuffer_.readFd(fd_, nullptr);
     if(ret == -1) {
         return;
     }
     else if(ret == 0){
         //close
     }
 }

 void TcpConnection::handleWrite(){
     int ret = outPutBuffer_.writeFd(fd_, nullptr);
     if(ret == -1){
         return;
     }
     else if(ret == 0){
         //close
     }
 }