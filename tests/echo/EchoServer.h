#pragma once
#include"IPAddress.h"
#include"EVentLoop.h"
#include"../net/Acceptor.h"
#include<memory>
class EchoHandler;

class EchoServer{
public:
    EchoServer(const IPAddress &listenAddr);
    void run();
private:
    std::shared_ptr<Acceptor<EchoHandler>> acceptor_;
    EventLoopPtr loop_;
    int listenfd_;
};