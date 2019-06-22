#pragma once
#include"EventHandler.h"

class Acceptor : public EventHandler{
public:
    Acceptor(int fd, uint32_t events, std::shared_ptr<EventLoop> &loop);
    void handleRead() override;
};