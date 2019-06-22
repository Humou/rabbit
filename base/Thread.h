#pragma once
#include"BlockingQueue.h"

#include<thread>
#include<memory>
#include<pthread.h>
#include<functional>

class TcpConnection;
class Thread{
public:
    Thread(std::function<void()> &thrFunc);

private:
    std::thread thread_;
};