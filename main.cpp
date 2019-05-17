#include"base/Socket.h"
#include"http/HttpRequest.h"

#include<thread>
#include<functional>
#include<sys/types.h>
#include<sys/socket.h>
#include<unordered_map>

void handle(Socket clinetSocket){
   while(true){
    char buf[1024];
    int len = clinetSocket.read((void*)buf, 1024);

    std::string requestStr(buf, len);
    HttpRequest req(requestStr);
    req.print();
    /*
    //printf("requestStr:\n%s\n", requestStr.c_str());
    size_t pos = requestStr.find("\r\n\r\n");

    std::string requestHead;
    std::string requestBody;

    if(pos == std::string::npos){
      requestHead =  std::string (requestStr.begin(), requestStr.end());
    }
    else{
        requestHead =  std::string (requestStr.begin(), requestStr.begin() + pos);
        pos = pos + 2;
        if(pos < requestStr.size())requestBody =  std::string (requestStr.begin() + pos, requestStr.end());
    }
    
    //printf("request head: %s\n", requestHead.c_str());

    pos = requestHead.find('\n');
    std::string requestLine(requestHead.begin(), requestHead.begin() + pos);

    printf("request line: %s\n", requestLine.c_str());
    //parser head parameter
    std::unordered_map<std::string, std::string> headParameters;
    
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

        headParameters[name] = value;
    }
    
    //parser request line
    pos = requestLine.find(' ');
    std::string requestMethod(requestLine.begin(), requestLine.begin() + pos);

    size_t bg = pos + 1;
    pos = requestLine.find(' ', bg);
     std::string requestPath(requestLine.begin() + bg, requestLine.begin() + pos);

    bg = pos + 1;
    //pos = requestLine.find(' ', bg);
     std::string requestVersion(requestLine.begin() + bg, requestLine.end());
    for(auto &p : headParameters){
        printf("%s = %s\n", p.first.c_str(), p.second.c_str());
    }

    printf("request method: %s\n", requestMethod.c_str());
    printf("request path: %s\n", requestPath.c_str());
    printf("request version: %s\n", requestVersion.c_str());
    // std::string message("OK");
     //clinetSocket.write_n((void*)message.data(), message.size());
     //clinetSocket.closeOrDie();
     */
   }
}

int main(int argc, char* argv[]){
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if(listenfd == -1){
        perror("listen failed");
        exit(-1);
    }

    int on = 1;
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
    Socket listenSocket(listenfd); 
    listenSocket.bindOrDie(IPAddress("0.0.0.0", 80));
    listenSocket.listenOrDie(20);

    int clientfd;
    std::thread thr;
    while((clientfd = listenSocket.acceptOrDie()) != -1){
        Socket clientSocket(clientfd);
        thr = std::thread(handle, clientSocket);
    }
    thr.join();
}
