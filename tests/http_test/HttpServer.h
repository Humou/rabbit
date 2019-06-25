#pragma once
#include"../../net/Acceptor.h"
#include"../../base/IPAddress.h"
#include"../../net/EVentLoop.h"

class HttpHandler;
class HttpServer{
public:
    HttpServer(const IPAddress &listenAddr);
    void run();
private:
    EventLoopPtr loop_;
    int listenfd_;
    std::shared_ptr<Acceptor<HttpHandler>> acceptor_;
};