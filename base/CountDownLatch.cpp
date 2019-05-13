#include"CountDownLatch.h"

void CountDownLatch::wait(){
    MutexGuard lock(mutex_);
    while(count_ > 0)
        con_.wait();
}

void CountDownLatch::countDown(){
    MutexGuard lock(mutex_);
    count_--;
    if(count_ == 0)
        con_.notifyAll();
}

int CountDownLatch::getCount() const{
    MutexGuard lock(mutex_);
    return count_;
}