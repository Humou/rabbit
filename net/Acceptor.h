#pragma once
#include"EventHandler.h"

#include <sys/types.h>   
#include <sys/socket.h>


template <typename Handler>
class Acceptor : public EventHandler{
public:
   Acceptor(int fd, uint32_t events, std::shared_ptr<EventLoop> &loop)
    :EventHandler(fd, EPOLLIN, loop)
    {

    }


    void handleRead() override{
        int clientfd = ::accept4(fd_, NULL, NULL, SOCK_NONBLOCK);
        std::shared_ptr<Handler> handler = std::make_shared<Handler>(clientfd, loop_);
        handler->registerToLoop();
    }

};