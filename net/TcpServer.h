#pragma once
#include"LoopThread.h"
#include"./Acceptor.h"
#include"../base/Logger.h"
#include"../base/Socket.h"
#include"../base/IPAddress.h"
#include"../net/EVentLoop.h"
#include"../base/CountDownLatch.h"

#include<vector>
#include<iostream>
template<typename Handler>
class TcpServer{
public:
    TcpServer(const IPAddress &listenAddr, int numThread)
    {
        assert(numThread>=1);
        loop_  = std::make_shared<EventLoop>();

        if(numThread - 1 > 0){
            countDownLatch_ = std::make_shared<CountDownLatch>(numThread - 1);
            for(int i = 0; i < numThread - 1; i++){
            auto thread = std::make_shared<LoopThread>(countDownLatch_);
            thread->run();
            loopThreads_.push_back(thread);
        }
        countDownLatch_->wait();
        }

        listenfd_ = Socket::createListenFd(listenAddr);
        if(listenfd_ == -1) {
            perror("HttpServer::HttpServer(const IPAddress &listenAddr)");
            return;
        }
    }

    void run(){
        Socket::listenOrDie(listenfd_, 100);
        auto loop = loadBalance();
        acceptor_ = std::make_shared<Acceptor<HttpHandler>>(listenfd_, EPOLLIN, loop);
        acceptor_->setNewConnectionCallBack(std::bind(&TcpServer::NewConnection, this, std::placeholders::_1));
        acceptor_->registerToLoop();
        loop_->loop();
    }

    EventLoopPtr loadBalance(){
        if(loopThreads_.size() == 0) return loop_;
        assert(curLoopThread_>=0 && curLoopThread_ < loopThreads_.size());
        auto &loopThread = loopThreads_[curLoopThread_];
        curLoopThread_ = (curLoopThread_ + 1)%loopThreads_.size();
        return loopThread->loop();
    }

    void NewConnection(int clientfd){
        Log(LogLevel::INFO, "NewConnection");
        auto loop = loadBalance();
        std::shared_ptr<Handler> handler = std::make_shared<Handler>(clientfd, loop);
        handler->registerToLoop();
    }

private:
    EventLoopPtr loop_;
    std::vector<std::shared_ptr<LoopThread>> loopThreads_;
    int listenfd_;
    std::shared_ptr<Acceptor<Handler>> acceptor_;
    int curLoopThread_ = 0;
    std::shared_ptr<CountDownLatch> countDownLatch_;
};