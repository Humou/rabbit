#include"Bridge.h"
#include<stdlib.h>
#include<sys/epoll.h>

Bridge::Bridge(int fd,  std::shared_ptr<EventLoop>  &loop)
    : fd_(fd),
      loop_(loop)
    {}
void Bridge::handleEvents(){
    if(revents_ & EPOLLIN){
        //read
        if(readCallBack_) readCallBack_();
    }

    if(revents_ & EPOLLOUT){
        //write
        if(writeCallBack_) writeCallBack_();
    }

    if(revents_ & EPOLLRDHUP){
        //peer shutdown write or close connection

    }

    if(revents_ & EPOLLPRI){
        
    }

}