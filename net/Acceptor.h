#pragma once
#include"EventHandler.h"
#include"../base/Logger.h"
#include"../base/callback.h"

#include<iostream>
#include <sys/types.h>   
#include <sys/socket.h>


template <typename Handler>
class Acceptor : public EventHandler{
public:
   Acceptor(int fd, uint32_t events, std::shared_ptr<EventLoop> &loop)
    :EventHandler(fd, events, loop)
    {

    }

    void handleRead() override{
        int clientfd = ::accept4(fd_, NULL, NULL, SOCK_NONBLOCK);
        if(clientfd == -1){
            Log(LogLevel::ERROR, "acceptor failed");
            return;
        } 
        if(newConnectionCallBack_){
            newConnectionCallBack_(clientfd);
        }
    }

    void setNewConnectionCallBack(NewConnectionCallBack newConnectionCallBack){
        newConnectionCallBack_ = newConnectionCallBack;
    }
private:
    NewConnectionCallBack newConnectionCallBack_;
};