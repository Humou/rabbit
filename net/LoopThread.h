#pragma once
#include"./EVentLoop.h"
#include"../base/CountDownLatch.h"

#include<thread>
class LoopThread{
public:
    LoopThread(std::shared_ptr<CountDownLatch> countDownLatch);
    void run();
    EventLoopPtr loop(){return loop_;}

    EventLoopPtr loop_;
    std::thread thread_;
    pthread_t threadId_;
    std::shared_ptr<CountDownLatch> countDownLatch_;
};