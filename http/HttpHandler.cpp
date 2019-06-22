#include"HttpHandler.h"
#include"HttpParser.h"
#include"HttpRequest.h"
#include"HttpResponse.h"
#include<iostream>
#include<unistd.h>
#include<stdio.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
HttpHandler::HttpHandler(int fd, uint32_t events, std::shared_ptr<EventLoop> &loop)
:EventHandler(fd, events, loop)
{

}

void HttpHandler::handleRead(){
   inputBuffer_.readFd(fd_, nullptr);
   auto message = inputBuffer_.retrieveAllASString();
   auto request = HttpParser::httpRequestFromString(message);
   auto response = handleRequest(request);
   outPutBuffer_.append(response.message().c_str(), response.message().size());
}

void HttpHandler::handleWrite(){
   outPutBuffer_.writeFd(fd_, nullptr);
 }

 HttpResponse HttpHandler::handleRequest(const HttpRequest &req){
    if(req.method == "GET"){
      int fd_;
      if((fd_ = ::open(req.path.c_str(), O_RDONLY)) == -1){
         //to do
         perror("HttpHandler::handleRequest(const HttpRequest &req)");
         return HttpResponse();
      }

      struct stat statBuf;
      if(fstat(fd_, &statBuf) == -1){
         //to do
         perror("HttpHandler::handleRequest(const HttpRequest &req)");
         return HttpResponse();
      }
      off_t sz = statBuf.st_size;
      char buf[sz];
      int rd = 0;
      int ret;
      ret = read(fd_, buf + rd, sz - rd);
      if(ret == -1){
         perror("HttpHandler::handleRequest(const HttpRequest &req)");
         return HttpResponse();
      }
      rd += ret;
      /* 
      while((ret = read(fd_, buf + rd, sz - rd))){
         if(ret == -1){
            if(errno == EINTR) continue;
            else break;
         }
         else if(ret == 0){
            break;
         }
         rd += ret;
      }
      */
      if(ret == -1){
         //to do
         perror("HttpHandler::handleRequest(const HttpRequest &req)");
         return HttpResponse();
      }

      std::string reponseContent(buf, rd);

      std::string message;
      message += "HTTP/1.0 200 OK\n";
      message += "Content-Type: text/html\n";
      message += "Content-Length: " + reponseContent.size();

      message += "\r\n\r\n";
      message += reponseContent;
      HttpResponse response;
      response.set_message( message);
      return response;
    }

    return HttpResponse();
 }