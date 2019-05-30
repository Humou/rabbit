#include"Epoller.h"

#include<stdio.h>
#include<stdlib.h>
#include<sys/epoll.h>

Epoller::Epoller(){
    epoll_fd_ = ::epoll_create(100);
    if(epoll_fd_ == -1){
        perror("Epoller::Epoller()");
        exit(1);
    }
}

void Epoller::addBridge(BridgePtr &bridge){
    epoll_event evt;
    int fd = bridge->fd();
    evt.events = bridge->event(); 
    evt.data.fd = fd;

    int ret = ::epoll_ctl(epoll_fd_, EPOLL_CTL_ADD, bridge->fd(), &evt);
    if(ret == -1){
        perror("Epoller::addBridge()");
        exit(1);
    }
     bridges_.push_back(bridge);
    fdToBridges_[fd] = bridges_.size() - 1;
}

void Epoller::removeBridge(BridgePtr &bridge){
    int fd = bridge->fd();
    int idx = fdToBridges_[fd];
    bridges_.erase(bridges_.begin() + idx);
    fdToBridges_.erase(fd);
}

std::vector<BridgePtr> Epoller::poll(){
    std::vector<epoll_event> events(bridges_.size());
    int numEvents = epoll_wait(epoll_fd_, events.data(), events.size(), -1);
    if(numEvents == -1){
        perror("Epoller::poll()");
        exit(1);
    }

    std::vector<BridgePtr> activeBriges;
    for(int i = 0; i < numEvents; i++){
        int fd = events[i].data.fd;
        int idx = fdToBridges_[fd];
        auto bridge = bridges_[idx];
        bridge->set_revents(events[i].events);
        activeBriges.push_back(bridges_[idx]);
    }

    return activeBriges;
}

