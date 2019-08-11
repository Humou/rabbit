#include"Thread.h"


Thread::Thread(std::function<void()> &thrFunc)
    :thread_(thrFunc)
{  
    
}