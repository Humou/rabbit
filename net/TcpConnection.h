#pragma once

#include"Buffer.h"
#include"Bridge.h"
#include"EVentLoop.h"

class TcpConnection{
public:
    TcpConnection(int fd, EventLoopPtr &eventLoop);
    void handleRead();
    void handleWrite();
private:
    Buffer inputBuffer_;
    Buffer outPutBuffer_;

    int fd_;
    EventLoopPtr loop_;
    BridgePtr bridge_;
};

using TcpConnectionPtr = std::shared_ptr<TcpConnection>;