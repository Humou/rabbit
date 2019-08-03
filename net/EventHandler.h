#pragma once

#include<memory>
#include<sys/epoll.h>

class EventLoop;
class EventHandler :public std::enable_shared_from_this<EventHandler>{
public:
    EventHandler(int fd, uint32_t events, std::shared_ptr<EventLoop> &loop);

    void handleEvents();

    virtual void handleRead();
    virtual void handleWrite();

    virtual void handleClose();
    virtual void handleError();
    
    void registerToLoop();

    int fd(){return fd_;}
    int events(){return events_;}
    void set_revents(int revents){revents_= revents;}

    void shutWrite();

protected:
    int fd_;
    std::shared_ptr<EventLoop> loop_;
    uint32_t events_ = 0;
    uint32_t revents_;
};