#pragma once
#include<vector>

#include"../base/IPAddress.h"
#include"../base/Socket.h"
#include"TcpConnection.h"
#include"EVentLoop.h"

class TcpServer{
public:
    TcpServer(const IPAddress &listenAddr);

    void run();
private:
    std::vector<TcpConnectionPtr> conections;
    int listenfd_;
    IPAddress listenAddr_;
    bool running_ = true;
    
    EventLoopPtr loop_;
};