#include"Bridge.h"
#include<stdlib.h>
#include<sys/epoll.h>
#include<iostream>

Bridge::Bridge(int fd,  std::shared_ptr<EventLoop>  &loop)
    : fd_(fd),
      loop_(loop)
    {}
void Bridge::handleEvents(){
    //std::cout<<"events: "<<events_<<std::endl;
    //std::cout<<"revents: "<<revents_<<std::endl;

    //std::cout<<"EPOLLIN: "<<EPOLLIN<<std::endl;
    //std::cout<<"EPOLLOUT: "<<EPOLLOUT<<std::endl;
    //std::cout<<"EPOLLPRI: "<<EPOLLPRI<<std::endl;
    //std::cout<<"EPOLLRDHUP: "<<EPOLLRDHUP<<std::endl;
    //std::cout<<"EPOLLIN | EPOLLPRI | EPOLLRDHUP: "<<(EPOLLIN | EPOLLPRI | EPOLLRDHUP)<<std::endl;
    if(revents_ & EPOLLIN ){
        //read
        if(readCallBack_){
            readCallBack_();
        }

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