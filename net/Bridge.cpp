#include"Bridge.h"

#include <unistd.h>
#include<stdlib.h>
#include<sys/epoll.h>
#include<iostream>

Bridge::Bridge(int fd,  std::shared_ptr<EventLoop>  &loop)
    : fd_(fd),
      loop_(loop)
    {}
    
void Bridge::handleEvents(){
    if(revents_ & EPOLLIN ){
        //read
       if(handleRead_) handleRead_();

    }

    if(revents_ & EPOLLOUT){
        //write
        if(handleWrite_) handleWrite_();
    }

    if(revents_ & EPOLLRDHUP){
        //peer shutdown write or close connection eof
        if(handleDisConn_) handleDisConn_();

    }
    if(revents_ & EPOLLPRI){
        //emerging data 
    }
    if(revents_ & EPOLLHUP){
        //peer close
        ::close(fd_);
    }

    if(revents_ & EPOLLERR){
        //err
        if(handleError_) handleError_();
    }
}
////
void Bridge::enableReading(){
    events_ |= EPOLLIN;
}

void Bridge::enableWriting(){
    events_ = events_ | EPOLLOUT;
}
