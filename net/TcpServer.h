#pragma once
#include"Socket.h"
#include"EVentLoop.h"
#include"IPAddress.h"
#include"TcpConnection.h"

#include<vector>

class TcpServer{
public:
    TcpServer(const IPAddress &listenAddr);

    void run();
    void readCallBack(std::shared_ptr<TcpConnection> conn);
    void writeCallBack(std::shared_ptr<TcpConnection> conn);

    void connectionCallback(std::shared_ptr<TcpConnection> listenConn);
    
private:
    std::vector<TcpConnectionPtr> conections;
    int listenfd_;
    IPAddress listenAddr_;
    bool running_ = true;
    
    EventLoopPtr loop_;
    Buffer buf_;
};