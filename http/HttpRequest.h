#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

#include"../base/Socket.h"
#include<string>
#include<unordered_map>

class HttpRequest{
public:
    HttpRequest(const std::string &message, SocketPtr socket);
    void print();
    void printHead();
 
    std::string method;
    std::string version;
    std::string path;
    
    std::string content;
    std::unordered_map<std::string, std::string> parameters;

    SocketPtr sock_;
};

#endif