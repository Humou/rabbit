#include"TcpServer.h"

int main(){
    TcpServer server(IPAddress("127.0.0.1", 4000));
    server.run();
}