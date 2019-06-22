#include"HttpHandler.h"
#include<unistd.h>
#include<stdio.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
/* 
 void HttpHandler::handler(){
   if(httpReq_.method == "GET"){
      int fd_;
      if((fd_ = ::open(httpReq_.path.c_str(), O_RDONLY)) == -1){
         //to do
         return;
      }

      struct stat statBuf;
      if(fstat(fd_, &statBuf) == -1){
         //to do
         return;
      }
      off_t sz = statBuf.st_size;
      char buf[sz];
      int rd = 0;
      int ret;
      while((ret = read(fd_, buf + rd, sz - rd))){
         if(ret == -1){
            if(errno == EINTR) continue;
            else break;
         }

         rd += ret;
      }

      if(ret == -1){
         //to do
         return;
      }

      std::string reponseContent(buf, rd);

      std::string reponseStr;
      reponseStr += "HTTP/1.0 200 OK\n";
      reponseStr += "Content-Type: text/html\n";
      reponseStr += "Content-Length: " + reponseContent.size();

      reponseStr += "\r\n\r\n";
      reponseStr += reponseContent;
      printf("response: %s\n", reponseStr.c_str());
      httpReq_.sock_->write_n((void*)reponseStr.c_str(), reponseStr.size());
      httpReq_.sock_->closeOrDie();
    }

 }
 */
HttpHandler::HttpHandler(int fd, uint32_t events, std::shared_ptr<EventLoop> &loop)
:EventHandler(fd_, events, loop)
{

}