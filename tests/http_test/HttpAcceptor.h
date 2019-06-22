#pragma once
#include"../../net/EventHandler.h"

class HttpAcceptor : public EventHandler{
public:
    HttpAcceptor(int fd, uint32_t events, std::shared_ptr<EventLoop> &loop);
    void handleRead() override;
};