#include"HttpHandler.h"
#include"HttpRequest.h"
#include"HttpResponse.h"
#include"../base/Logger.h"

#include<iostream>
#include<unistd.h>
#include<stdio.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h> 

HttpHandler::HttpHandler(int fd, std::shared_ptr<EventLoop> &loop)
:EventHandler(fd, EPOLLIN|EPOLLOUT, loop), parseState_(ParseState::RequestLine)
{

}

void HttpHandler::handleRead(){
   int rd = inputBuffer_.readFd(fd_, nullptr);
   if(rd == 0){
      ::close(fd_);
      return;
   }

   if(!parseRequest(&inputBuffer_)){
      outPutBuffer_.append("HTTP/1.1 400 Bad Request/r/n/r/n");
      shutWrite();
   }

   if(parseState_ == ParseState::GotAll){
      auto response = handleRequest();
      outPutBuffer_.append(response.message());
      const std::string& connection = request_.getHeader("Connection");

      if(connection == "Keep-Alive"){
         parseState_ = ParseState::RequestLine;
      }
      else{
         shutWrite();
      }
   }
}

void HttpHandler::handleWrite(){
   outPutBuffer_.writeFd(fd_, nullptr);
 }

 bool HttpHandler::processRequestLine(const char* begin, const char* end){
    bool succeed = false;
  const char* start = begin;
  const char* space = std::find(start, end, ' ');
  if (space != end && request_.setMethod(start, space))
  {
    start = space+1;
    space = std::find(start, end, ' ');
    if (space != end)
    {
      const char* question = std::find(start, space, '?');
      if (question != space)
      {
        request_.setPath(start, question);
        request_.setQuery(question, space);
      }
      else
      {
        request_.setPath(start, space);
      }
      start = space+1;
      succeed = end-start == 8 && std::equal(start, end-1, "HTTP/1.");
      if (succeed)
      {
        if (*(end-1) == '1')
        {
          request_.setVersion(HttpRequest::kHttp11);
        }
        else if (*(end-1) == '0')
        {
          request_.setVersion(HttpRequest::kHttp10);
        }
        else
        {
          succeed = false;
        }
      }
    }
  }
  return succeed;
 }

 bool HttpHandler::parseRequest(Buffer* buf){
  bool ok = true;
  bool hasMore = true;
  while (hasMore)
  {
    if (parseState_ == ParseState::RequestLine)
    {
      const char* crlf = buf->findCRLF();
      if (crlf)
      {
        ok = processRequestLine(buf->peek(), crlf);
        if (ok)
        {
          //request_.setReceiveTime(receiveTime);
          buf->retrieveUntil(crlf + 2);
          parseState_ = ParseState::RequestHeaders;
        }
        else
        {
          hasMore = false;
        }
      }
      else
      {
        hasMore = false;
      }
    }
    else if (parseState_ == ParseState::RequestHeaders)
    {
      const char* crlf = buf->findCRLF();
      if (crlf)
      {
        const char* colon = std::find(buf->peek(), crlf, ':');
        if (colon != crlf)
        {
           
          request_.addHeader(buf->peek(), colon, crlf);
        }
        else
        {
          // empty line, end of header
          // FIXME:
          parseState_ = ParseState::GotAll;
          hasMore = false;
        }
        buf->retrieveUntil(crlf + 2);
      }
      else
      {
        hasMore = false;
      }
    }
    else if (parseState_ == ParseState::GotAll)
    {
      // FIXME:
    }
  }
  return ok;

 }

std::string HttpHandler::contents(){
   int fd;
   std::string path = "." + request_.path();
   if((fd = ::open(path.c_str(), O_RDONLY)) == -1){
      //to do
      Log(LogLevel::INFO, "open failed");
      return "";
   }

   struct stat statBuf;
   if(fstat(fd, &statBuf) == -1){
      //to do
      Log(LogLevel::INFO, "fstat failed");
      return "";
   }
   off_t sz = statBuf.st_size;
   char buf[sz];
   int rd = 0;
   int ret;
   ret = read(fd, buf + rd, sz - rd);
   if(ret == -1){
      Log(LogLevel::INFO, "read failed");
      return "";
   }
   rd += ret;

   return std::string(buf, rd);
}
HttpResponse HttpHandler::handleRequest(){
    if(request_.methodString() == "GET"){
      HttpResponse response;

      response.set_responseCode(ResponseCode::OK);
      response.set_keekAlive(false);
      response.set_contents(contents());
      return response;
    }
   else if(request_.methodString() == "HEAD"){

   }
   return HttpResponse();
}
