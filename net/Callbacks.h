#pragma once
#include<functional>

class TcpConnection;
using ReadCallBack = std::function<void(std::shared_ptr<TcpConnection> conn)>;
using WriteCallBack = std::function<void(std::shared_ptr<TcpConnection> conn)>;
using ConnectionCallBack = std::function<void(std::shared_ptr<TcpConnection> conn)>;
using DisConnectionCallBack = std::function<void(std::shared_ptr<TcpConnection> conn)>;
using ErrorCallBack = std::function<void(std::shared_ptr<TcpConnection> conn)>;