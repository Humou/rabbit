#pragma once
#include"IPAddress.h"
#include<memory>

class TcpConnection;
class EventLoop;
class TcpClient{
public:
    TcpClient(const IPAddress &serverAddr, const std::shared_ptr<EventLoop> loop);
    ~TcpClient();

    void connect();
    void readCallBack(std::shared_ptr<TcpConnection> conn);
    void writeCallBack(std::shared_ptr<TcpConnection> conn);
private:
    std::shared_ptr<TcpConnection> conn;
    std::shared_ptr<EventLoop> loop_;
    int clientfd_;
    IPAddress serverAddr_;        
};