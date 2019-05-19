#ifndef HTTPHANDLER_H
#define HTTPHANDLER_H
#include"HttpRequest.h"

class HttpHandler{
public:
    HttpHandler(const HttpRequest &httpRequest)
    : httpReq_(httpRequest){}

    void handler();

private:
    HttpRequest httpReq_;
};

#endif