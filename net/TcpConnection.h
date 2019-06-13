#pragma once

#include"Buffer.h"
#include"Bridge.h"
#include"EVentLoop.h"

#include<memory>
#include<iostream>
class TcpConnection : public std::enable_shared_from_this<TcpConnection>{
public:
    TcpConnection(int fd, EventLoopPtr &eventLoop);

    void handleRead();
    void handleWrite();
    void handleConnection();
    
    void registerToLoop();
    void setReadCallBack(ReadCallBack cb);
    void setWriteCalBack(WriteCallBack cb);
    void setConnectionCallBack(ConnectionCallBack cb){ connectionCallBack_ = cb;}

    std::string readAllAsString(){return inputBuffer_.retrieveAllASString();}
    void writeString(const std::string &s){outPutBuffer_.append(s.c_str(), s.size());}
private:
    Buffer inputBuffer_;
    Buffer outPutBuffer_;

    int fd_;
    EventLoopPtr loop_;
    BridgePtr bridge_;
    ReadCallBack readCallBack_;
    WriteCallBack writeCallBack_;
    ConnectionCallBack connectionCallBack_;
};

using TcpConnectionPtr = std::shared_ptr<TcpConnection>;