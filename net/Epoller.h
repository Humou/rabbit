#ifndef EPOLLER_H
#define EPOLLER_H
#include"Bridge.h"

#include<vector>
#include<unordered_map>

class Epoller{
public:
    Epoller();
    void addBridge(BridgePtr &bridge);
    void removeBridge(BridgePtr &bridge);
    std::vector<BridgePtr> bridges(){return bridges_;}
    std::vector<BridgePtr> poll();
private:
    int epoll_fd_ = -1;
    std::vector<BridgePtr> bridges_;
    std::unordered_map<int, int> fdToBridges_;
};
#endif