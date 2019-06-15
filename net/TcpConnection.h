#pragma once

#include"Buffer.h"
#include"Bridge.h"
#include"EVentLoop.h"

#include<memory>
#include <unistd.h>
#include<iostream>
class TcpConnection : public std::enable_shared_from_this<TcpConnection>{
public:
    TcpConnection(int fd, EventLoopPtr &eventLoop);
    void handleRead();
    void handleWrite();
    void handleError();
    void handleDisConn();

    void registerToLoop();

    void set_readCallBack(ReadCallBack cb){ readCallBack_ = cb; }
    void set_writeCalBack(WriteCallBack cb){ writeCallBack_ = cb; }
    void set_connCallBack(ConnectionCallBack cb){ connCallBack_ = cb;}

    void set_errorCallBack(ErrorCallBack cb){ errorCallBack_ = cb; }
    void set_disConnCallBack(DisConnectionCallBack cb){disConnCallBack_ = cb;}
    
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
    ErrorCallBack errorCallBack_;

    ConnectionCallBack connCallBack_;
    DisConnectionCallBack disConnCallBack_;
};

using TcpConnectionPtr = std::shared_ptr<TcpConnection>;