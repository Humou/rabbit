#include"TcpClient.h"
#include"EVentLoop.h"
int main(){
    IPAddress addr("127.0.0.1", 4000);
    std::shared_ptr<EventLoop> loop = std::make_shared<EventLoop>();
    TcpClient client(addr, loop);
    client.connect();
    return 0;
}