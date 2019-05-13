#ifndef BLOCKINGQUEUE_H
#define BLOCKINGQUEUE_H
#include"Condition.h"

#include<queue>
template<typename T>
class BlockingQueue{
public:
    BlockingQueue()
    :
    mutex_(),
    con_(mutex_),
    queue_()
    {}

    void put(const T &x){
        MutexGuard lock(mutex_);
        queue_.push(x);
        notEmpty_.notify();
    }

    T take(){
        MutexGuard lock(mutex_);
        while(queue_.empty())
            notEmpty_.wait();
        
        T front(queue_.front());
        queue_.pop();
        return front;
    }

    int size() const{
        MutexGuard lock(mutex_);
        return queue_.size();
    }
private:
    Mutex mutex_;
    Condition notEmpty_;
    std::queue<T> queue_;
};

#endif