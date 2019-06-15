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
    
    void set_handleRead(std::function<void()> cb){
        handleRead_ = cb;
        events_ |= EPOLLIN;
    }

     void set_handleWrite(std::function<void()> cb){
        handleWrite_ = cb;
        events_ = events_ | EPOLLOUT;
    }

    void set_handleConn(std::function<void()> cb){
        handleConn_ = cb;
    }

    void set_handleDisConn(std::function<void()> cb){
        handleDisConn_ = cb;
    }

    void set_handleError(std::function<void()> cb){
        handleError_ = cb;
    }

    void enableReading();
    void enableWriting();

private:
    uint32_t events_ = 0;
    uint32_t revents_;
    int fd_;
    std::shared_ptr<EventLoop> loop_;

    std::function<void()> handleRead_;
    std::function<void()> handleWrite_;
    std::function<void()> handleError_;
    std::function<void()> handleDisConn_;
    std::function<void()> handleConn_;
 };

using BridgePtr = std::shared_ptr<Bridge>; 

