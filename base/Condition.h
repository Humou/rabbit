#ifndef CONDITION_H
#define CONDITION_H
#include"Mutex.h"

#include<pthread.h>

class Condition{
public:
    explicit Condition(Mutex &mutex)
    :mutex_(mutex)
    {
        pthread_cond_init(&con_, NULL);
    }
    
    ~Condition(){
        pthread_cond_destroy(&con_);
    }

    int wait(){
        return pthread_cond_wait(&con_, mutex_.getMutexPtr());
    }

    int notify(){
        return pthread_cond_signal(&con_);
    }

    int notifyAll(){
        return pthread_cond_broadcast(&con_);
    }

private:
 Mutex mutex_;
    pthread_cond_t con_;
};
#endif