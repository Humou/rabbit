#pragma once
#include"Epoller.h"

class EventLoop{
public:
    EventLoop();
    ~EventLoop();
    void loop();

    void addBridge(BridgePtr &birdge);
    void removeBirdge(BridgePtr &birdge);
    
    Epoller poller_;
};

using EventLoopPtr = std::shared_ptr<EventLoop>;