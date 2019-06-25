#pragma once
#include<string>
#include<unordered_map>
enum class HttpMethod{
    GET, POST, HEAD, PUT, DELETE
};

class HttpRequest{
public:
    //void print();
    //void printHead();
 
    std::string method_;
    std::string version_;
    std::string path_;
    
    std::string content_;
    std::unordered_map<std::string, std::string> headers_;
};
