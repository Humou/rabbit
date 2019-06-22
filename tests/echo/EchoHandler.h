#pragma once
#include"Buffer.h"
#include"EventHandler.h"
class EchoHandler : public EventHandler{
public:
    EchoHandler(int fd, uint32_t events, std::shared_ptr<EventLoop> &loop);
    void handleRead() override;
    void handleWrite() override;
    void handleClose() override;
private:
    Buffer buffer_;
};