#ifndef COUNTDOWNLATCH_H
#define COUNTDOWNLATCH_H
#include"Condition.h"

class CountDownLatch{
public:
    CountDownLatch(int count)
    : 
    count_(count),
    mutex_(),
    con_(mutex_) {}

    void wait();
    void countDown();
    int getCount() const;
private:
    mutable Mutex mutex_;
    Condition con_;
    int count_;
};

#endif