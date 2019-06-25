#include"HttpHandler.h"
#include"HttpParser.h"
#include"HttpRequest.h"
#include"HttpResponse.h"
#include"../base/Logger.h"

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
   //Log(LogLevel::INFO, "http request");
   int rd = inputBuffer_.readFd(fd_, nullptr);
   if(rd == 0){
      ::close(fd_);
      return;
   }
   auto message = inputBuffer_.retrieveAllASString();
   auto request = HttpParser::httpRequestFromString(message);
   std::cout<<"recv: "<<std::endl<<message<<std::endl;
   auto response = handleRequest(request);
   outPutBuffer_.append(response.message());
   std::cout<<"send: "<<std::endl<<response.message()<<std::endl;
}

void HttpHandler::handleWrite(){
   outPutBuffer_.writeFd(fd_, nullptr);
 }

 HttpResponse HttpHandler::handleRequest(const HttpRequest &req){
    if(req.method_ == "GET"){
      int fd_;
      if((fd_ = ::open(req.path_.c_str(), O_RDONLY)) == -1){
         //to do
         Log(LogLevel::INFO, "open failed");
         return HttpResponse();
      }

      struct stat statBuf;
      if(fstat(fd_, &statBuf) == -1){
         //to do
         Log(LogLevel::INFO, "fstat failed");
         return HttpResponse();
      }
      off_t sz = statBuf.st_size;
      char buf[sz];
      int rd = 0;
      int ret;
      ret = read(fd_, buf + rd, sz - rd);
      if(ret == -1){
         Log(LogLevel::INFO, "read failed");
         return HttpResponse();
      }
      rd += ret;

      std::string contents(buf, rd);
      HttpResponse response;

      response.set_responseCode(ResponseCode::OK);
      response.set_keekAlive(false);
      response.set_contents(contents);

      return response;
    }

    return HttpResponse();
 }