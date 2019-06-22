#include"HttpServer.h"

int main(){
    HttpServer server(IPAddress("127.0.0.1", 80));
    server.run();
}