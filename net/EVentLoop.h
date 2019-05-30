#pragma once
#include"Epoller.h"

class EventLoop{
public:
    EventLoop();
    ~EventLoop();
    void loop();

    Epoller poller;
};