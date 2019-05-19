#include"base/Socket.h"
#include"http/HttpRequest.h"
#include"http/HttpHandler.h"

#include<thread>
#include<functional>
#include<sys/types.h>
#include<sys/socket.h>
#include<unordered_map>

void handle(SocketPtr clientSocket){
    char buf[1024];
    int len = clientSocket->read((void*)buf, 1024);
    std::string requestStr(buf, len);
    HttpRequest req(requestStr, clientSocket);
    req.print();
    HttpHandler httpHandler(req);
    httpHandler.handler();
}

int main(int argc, char* argv[]){
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if(listenfd == -1){
        perror("listen failed");
        exit(-1);
    }

    int on = 1;
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
    SocketPtr listenSockPtr = std::make_shared<Socket>(listenfd); 
    listenSockPtr->bindOrDie(IPAddress("0.0.0.0", 80));
    listenSockPtr->listenOrDie(20);

    int clientfd;
    std::thread thr;
    while((clientfd = listenSockPtr->acceptOrDie()) != -1){
        SocketPtr clientSockPtr = std::make_shared<Socket>(clientfd);
        thr = std::thread(handle, clientSockPtr);
    }
    thr.join();
}
