#include"LoopThread.h"
#include<iostream>
void* threadFunc(void* obj){
    LoopThread* thread = static_cast<LoopThread*>(obj);
    thread->loop_ = std::make_shared<EventLoop>();
    thread->countDownLatch_->countDown();
    thread->loop_->loop();
    return NULL;
}

LoopThread::LoopThread(std::shared_ptr<CountDownLatch> countDownLatch)
    :countDownLatch_(countDownLatch)
{
}

void LoopThread::run(){
   std::cout<<"begin run"<<std::endl;
   auto ret = pthread_create(&threadId_, NULL, &threadFunc, this);
   if(ret == -1){
       perror("Failed in pthread_create");
       return;
   }
   std::cout<<"end run"<<std::endl;
}
