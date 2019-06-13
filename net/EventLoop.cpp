#include"EVentLoop.h"
#include<iostream>

EventLoop::EventLoop(){

}

EventLoop::~EventLoop(){

}

void EventLoop::loop(){
   while(1){
        auto activeBridges = poller_.poll();
        for(auto &bridge : activeBridges)
            bridge->handleEvents();
   }
}

void EventLoop::addBridge(BridgePtr &bridge){
   poller_.addBridge(bridge);
}

void EventLoop::removeBirdge(BridgePtr &bridge){
   poller_.removeBridge(bridge);
}

