#include"EVentLoop.h"

EventLoop::EventLoop(){

}

EventLoop::~EventLoop(){

}

void EventLoop::loop(){
   while(1){
        auto activeBridges = poller.poll();
        for(auto &bridge : activeBridges)
            bridge->handleEvents();
   }
}