#pragma once
#include<memory>
#include<stdint.h>
class Bridge{
public:
    uint32_t event(){return events_;}
    void set_revents(uint32_t revents){ revents_ = revents; }
    int fd(){return fd_;}
    void handleEvents();
    
private:
    uint32_t events_;
    uint32_t revents_;
    int fd_;
};

using BridgePtr = std::shared_ptr<Bridge>; 

