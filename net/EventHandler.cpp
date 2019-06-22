#include"EVentLoop.h"
#include"EventHandler.h"

#include <unistd.h>
#include<iostream>
EventHandler::EventHandler(int fd, uint32_t events, std::shared_ptr<EventLoop> &loop)
    :fd_(fd), events_(events), loop_(loop)
{
}
void EventHandler::handleEvents(){
    if((events_ & EPOLLIN) && (revents_ & EPOLLIN)){
        //read
        handleRead();
    }

    if((events_ & EPOLLOUT) && (revents_ & EPOLLOUT)){
        //write
       handleWrite();
    }

    if((events_ & EPOLLRDHUP) && (revents_ & EPOLLRDHUP)){
        //peer shutdown write or close connection eof
        handleClose();
    }

    if((events_ & EPOLLPRI) && (revents_ & EPOLLPRI)){
        //emerging data 
    }

    if((events_ & EPOLLHUP) && (revents_ & EPOLLHUP)){
    }

    if((events_ & EPOLLERR) && (revents_ & EPOLLERR)){
        //err
       handleError();
    }
}

void EventHandler::handleRead(){
    
}

void EventHandler::handleWrite(){

}
void EventHandler::handleClose(){

}
void EventHandler::handleError(){
    
}

void EventHandler::registerToLoop(){
    loop_->addEventHandler(shared_from_this());
}