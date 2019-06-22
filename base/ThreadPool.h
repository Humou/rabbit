#pragma once
#include"BlockingQueue.h"

#include<atomic>
#include<vector>
#include<thread>
#include<functional>

using Task = std::function<void()>;

class ThreadPool{
public:
    ThreadPool(int threadNum = 6);
    ~ThreadPool();
    void run();
    void addTask(Task task);

private:
    std::vector<std::thread> threads_;
    BlockingQueue<Task> tasks_;
    std::atomic<bool> isRunning_;
    int threadNum_;     
};