#include"Bridge.h"
#include<stdlib.h>
#include<sys/epoll.h>

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