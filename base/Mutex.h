#ifndef MUTEX_H
#define MUTEX_H
#include<pthread.h>

class Mutex{
public:
    Mutex(){
        pthread_mutex_init(&mutex_, NULL);
    }
    ~Mutex(){
        pthread_mutex_destroy(&mutex_);
    }

    int lock(){
        return pthread_mutex_lock(&mutex_);
    }

    int unlock(){
        return pthread_mutex_unlock(&mutex_);
    }

    pthread_mutex_t* getMutexPtr(){return &mutex_;}

private:
    pthread_mutex_t mutex_;
};

class MutexGuard{
public:
    MutexGuard(Mutex &mutex)
    :mutex_(mutex){
        mutex_.lock();
    }

    ~MutexGuard(){
        mutex_.unlock();
    }

private:
    Mutex &mutex_;
};
#endif //Mutex.h