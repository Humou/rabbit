#include"EVentLoop.h"
//#include"EchoHandler.h"
#include"EventHandler.h"
#include<iostream>
#include<sys/epoll.h>

EventLoop::EventLoop(){
   epoll_fd_ = ::epoll_create(100);
    if(epoll_fd_ == -1){
        perror("Epoller::Epoller()");
        exit(1);
    }
}

EventLoop::~EventLoop(){

}

void EventLoop::loop(){
   while(1){
        auto activeHandlers = poll();
        for(auto &handler : activeHandlers)
            handler->handleEvents();
   }
}


std::vector<std::shared_ptr<EventHandler>> EventLoop::poll(){
    if(handlers_.size() == 0) return std::vector<std::shared_ptr<EventHandler>>();
    std::vector<epoll_event> events(handlers_.size());
    int numEvents = epoll_wait(epoll_fd_, events.data(), events.size(), -1);
    if(numEvents == -1){
        perror("EventLoop::poll()");
        exit(1);
    }

    std::vector<std::shared_ptr<EventHandler>> activeHandlers;
    for(int i = 0; i < numEvents; i++){
        int fd = events[i].data.fd;
        int idx = fdToIdxs_[fd];
        auto handler = handlers_[idx];
        handler->set_revents(events[i].events);
        activeHandlers.push_back(handler);
    }
    return activeHandlers;
}
void EventLoop::addEventHandler(std::shared_ptr<EventHandler> handler){
   epoll_event evt;
    int fd = handler->fd();
    evt.events = handler->events(); 
    evt.data.fd = fd;
    int ret = ::epoll_ctl(epoll_fd_, EPOLL_CTL_ADD, fd, &evt);
    if(ret == -1){
        perror("EventLoop::addEventHandler()");
        exit(1);
    }
    handlers_.push_back(handler);
    fdToIdxs_[fd] = handlers_.size() - 1;
}

void EventLoop::removeEventHandler(std::shared_ptr<EventHandler> handler){
    int idx = fdToIdxs_[handler->fd()];
    std::swap(handlers_[idx], handlers_[handlers_.size() - 1]);
    handlers_.pop_back();

    fdToIdxs_.erase(handler->fd());
    fdToIdxs_[handlers_[idx]->fd()] = idx;
}