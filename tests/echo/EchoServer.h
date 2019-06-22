#pragma once
#include"IPAddress.h"
#include"EVentLoop.h"
#include<memory>
class Acceptor;
class EchoServer{
public:
    EchoServer(const IPAddress &listenAddr);
    void run();
private:
    std::shared_ptr<Acceptor> acceptor_;
    EventLoopPtr loop_;
    int listenfd_;
};