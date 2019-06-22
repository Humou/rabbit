#include"HttpRequest.h"

HttpRequest::HttpRequest(const std::string &message)
{
     size_t pos = message.find("\r\n\r\n");

    std::string requestHead;
    //std::string requestBody;

    if(pos == std::string::npos){
      requestHead =  std::string (message.begin(), message.end());
    }
    else{
        requestHead =  std::string (message.begin(), message.begin() + pos);
        pos = pos + 4;
        if(pos < message.size()) content =  std::string (message.begin() + pos, message.end());
    }
    
    pos = requestHead.find('\n');
    std::string requestLine(requestHead.begin(), requestHead.begin() + pos);

    //parser head parameter
    while(pos != std::string::npos){
        int bg = ++pos;
        int ed = requestHead.find('\n', pos);
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

        parameters[name] = value;
    }
    
    //parser request line
    pos = requestLine.find(' ');
    method = std::string(requestLine.begin(), requestLine.begin() + pos);

    size_t bg = pos + 1;
    pos = requestLine.find(' ', bg);
    path = std::string(requestLine.begin() + bg, requestLine.begin() + pos);
    path = "../res/html" + path;
    bg = pos + 1;
    version = std::string(requestLine.begin() + bg, requestLine.end());
}

void HttpRequest::print(){
    std::string reqLine = method+ ' ' + path + ' ' + version;
    printf("%s\n", reqLine.c_str());

    for(auto &p : parameters){
        std::string cur = p.first + ": " + p.second;
        printf("%s\n", cur.c_str());
    }

    if(parameters.size() > 0) printf("\n");
    else printf("\n\n");

    if(content.size() > 0) printf("%s\n", content.c_str());
}

void HttpRequest::printHead(){
    std::string reqLine = method+ ' ' + path + ' ' + version;
    printf("%s\n", reqLine.c_str());

    for(auto &p : parameters){
        std::string cur = p.first + ": " + p.second;
        printf("%s\n", cur.c_str());
    }
    printf("\n\n");
}