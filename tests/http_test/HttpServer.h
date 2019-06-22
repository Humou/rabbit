#pragma once
#include"HttpAcceptor.h"
#include"../../base/IPAddress.h"
#include"../../net/EVentLoop.h"
class HttpServer{
public:
    HttpServer(const IPAddress &listenAddr);
    void run();
private:
    EventLoopPtr loop_;
    int listenfd_;
    std::shared_ptr<HttpAcceptor> acceptor_;
};