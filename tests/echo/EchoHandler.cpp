#include"EchoHandler.h"
#include"EVentLoop.h"
#include<unistd.h>
#include<iostream>

EchoHandler::EchoHandler(int fd, uint32_t events, std::shared_ptr<EventLoop> &loop)
:EventHandler(fd, events, loop)
{

}

void EchoHandler::handleRead(){
     char buf[4096];
     int rw = ::read(fd_, buf, sizeof buf);
     if(rw == -1){
         perror(" EchoHandler::handleRead()");
         return;
     }
    buf[rw] = '\0';
    buffer_.append(buf, rw);
    printf("read: %s\n", buf);
}

void EchoHandler::handleWrite(){
    if(buffer_.readableBytes() == 0) return;
    int ret = buffer_.writeFd(fd_, nullptr);
    if(ret == -1){
        perror("EchoHandler::handleWrite()");
        return;
    }
}

void EchoHandler::handleClose(){
    //std::cout<<"handlePeerShutDown()"<<std::endl;
    if(buffer_.readableBytes() == 0){
        loop_->removeEventHandler(shared_from_this());
        close(fd_);
    }
}