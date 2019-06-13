#pragma once
#include<memory>
#include<stdint.h>
#include<sys/epoll.h>

#include"Callbacks.h"

class EventLoop;

class Bridge{
public:
    Bridge(int fd,  std::shared_ptr<EventLoop> &loop);

    
    uint32_t event(){return events_;}
    void set_revents(uint32_t revents){ revents_ = revents; }
    int fd(){return fd_;}
    void handleEvents();
    
    void setReadCallBack(std::function<void()> cb){
        readCallBack_ = cb;
        events_ |= EPOLLIN;
    }

    void setErrorCallBack(std::function<void()> cb){
        errorCallBack_ = cb;
    }

    void setWriteCallBack(std::function<void()> cb){
        writeCallBack_ = cb;
        events_ = events_ | EPOLLOUT;
    }
private:
    uint32_t events_ = 0;
    uint32_t revents_;
    int fd_;
    std::shared_ptr<EventLoop> loop_;

    std::function<void()> readCallBack_;
    std::function<void()> writeCallBack_;
    std::function<void()>  errorCallBack_;
};

using BridgePtr = std::shared_ptr<Bridge>; 

