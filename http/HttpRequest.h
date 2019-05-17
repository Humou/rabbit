#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

#include<string>
#include<unordered_map>

class HttpRequest{
public:
    HttpRequest(const std::string &message);
    void print();
    void printHead();
private:  
    std::string method;
    std::string version;
    std::string path;
    
    std::string content;
    std::unordered_map<std::string, std::string> parameters;
};

#endif