#include"../../base/IPAddress.h"
#include"../../http/HttpHandler.h"
#include"../../net/TcpServer.h"

#include<iostream>

int main(){

    TcpServer<HttpHandler> server(IPAddress("127.0.0.1", 80), 1);
    server.run();
}