#pragma once
#include<memory>
#include<stdint.h>
#include<sys/epoll.h>

#include"Callbacks.h"

class Bridge{
public:
    Bridge(int fd): fd_(fd){}
    
    uint32_t event(){return events_;}
    void set_revents(uint32_t revents){ revents_ = revents; }
    int fd(){return fd_;}
    void handleEvents();
    
    void setReadCallBack(ReadCallBack cb){
        readCallBack_ = cb;
        events_|= EPOLLIN;
    }

    void setWriteCallBack(WriteCallBack cb){
        writeCallBack_ = cb;
        events_ |= EPOLLOUT;
    }

    void setErrorCallBack(ErrorCallBack cb){
        errorCallBack_ = cb;
    }

private:
    uint32_t events_;
    uint32_t revents_;
    int fd_;

    ReadCallBack readCallBack_;
    WriteCallBack writeCallBack_;
    ErrorCallBack errorCallBack_;
};

using BridgePtr = std::shared_ptr<Bridge>; 

