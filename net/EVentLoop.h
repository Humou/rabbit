#pragma once
#include<memory>
#include<vector>
#include<unordered_map>
class EventHandler;
class EventLoop{
public:
    EventLoop();
    ~EventLoop();

    void loop();
    std::vector<std::shared_ptr<EventHandler>> poll();
    void addEventHandler(std::shared_ptr<EventHandler> handler);
    void removeEventHandler(std::shared_ptr<EventHandler> handler);


private:
    int epoll_fd_ = -1;
    std::vector<std::shared_ptr<EventHandler>> handlers_;
    std::unordered_map<int, int> fdToIdxs_;
};

using EventLoopPtr = std::shared_ptr<EventLoop>;