#include"Acceptor.h"
#include"EchoHandler.h"
#include <sys/types.h>      
#include <sys/socket.h>

Acceptor::Acceptor(int fd, uint32_t events, std::shared_ptr<EventLoop> &loop)
   :EventHandler(fd, events, loop)
{

}

void Acceptor::handleRead(){
   int clientfd = ::accept4(fd_, NULL, NULL, SOCK_NONBLOCK);
   auto echoHandler = std::make_shared<EchoHandler>(clientfd, EPOLLIN | EPOLLOUT|EPOLLRDHUP, loop_);
   echoHandler->registerToLoop();
}