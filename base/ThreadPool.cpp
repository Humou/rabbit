#include"ThreadPool.h"

ThreadPool::ThreadPool(int threadNum)
   : threadNum_(threadNum), isRunning_(true), threads_(threadNum)
{
   
}
ThreadPool::~ThreadPool(){
    for(auto &thr : threads_)
        if(thr.joinable()) thr.join();
}

 void ThreadPool::run(){
     auto thrFunc = [this]{
         while(isRunning_){
             auto task =tasks_.take();
             task();
         }
     };
     for(auto &thr : threads_){
         std::thread t(thrFunc);
         thr.swap(t);
     }
 }

 void ThreadPool::addTask(Task task){
     tasks_.put(task);
 }

