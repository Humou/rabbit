#include"HttpParser.h"
#include"HttpRequest.h"
#include<iostream>
HttpRequest HttpParser::httpRequestFromString(const std::string &message){
    HttpRequest req;
    size_t pos = message.find("\r\n\r\n");
    std::string requestHead;
    //std::string requestBody;

    if(pos == std::string::npos){
      requestHead =  std::string (message.begin(), message.end());
    }
    else{
        requestHead =  std::string (message.begin(), message.begin() + pos);
        pos = pos + 4;
        if(pos < message.size()) req.content_ =  std::string (message.begin() + pos, message.end());
    }
    
    pos = requestHead.find('\r\n');
    std::string requestLine(requestHead.begin(), requestHead.begin() + pos);

    //parser head parameter
    while(pos != std::string::npos){
        int bg = ++pos;
        int ed = requestHead.find('\r\n', pos);
        std::string line;
        if(ed == std::string::npos){
            line = std::string(requestHead.begin() + bg, requestHead.end());
        }
        else{
            line = std::string(requestHead.begin() + bg, requestHead.begin() + ed);
        }
        pos = ed;

        int colonPos = line.find(':');
        std::string name = std::string(line.begin(), line.begin() + colonPos);
        colonPos++;
        while(colonPos == ' ')
            colonPos++;
        std::string value(line.begin() + colonPos, line.end());

        req.headers_[name] = value;
    }
    
    //parser request line
    pos = requestLine.find(' ');
    req.method_ = std::string(requestLine.begin(), requestLine.begin() + pos);

    size_t bg = pos + 1;
    pos = requestLine.find(' ', bg);
    req.path_ = std::string(requestLine.begin() + bg, requestLine.begin() + pos);
    bg = pos + 1;
    req.version_ = std::string(requestLine.begin() + bg, requestLine.end());
    return req;
}