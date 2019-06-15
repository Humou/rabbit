#include"TcpClient.h"
#include"Logger.h"
#include"TcpConnection.h"
TcpClient::TcpClient(const IPAddress &serverAddr, const std::shared_ptr<EventLoop> loop)
:loop_(loop),
 serverAddr_(serverAddr) 
{
    clientfd_ = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(clientfd_ == -1){
        perror("TcpClient(const IPAddress &serverAddr)");
        return;
    }
    conn = std::make_shared<TcpConnection>(clientfd_, loop_);
    conn->set_readCallBack(std::bind(&TcpClient::readCallBack, this, std::placeholders::_1));
    conn->set_writeCalBack(std::bind(&TcpClient::writeCallBack, this, std::placeholders::_1));
    conn->registerToLoop();
}
TcpClient::~TcpClient(){

}
void TcpClient::connect(){
    auto addr = serverAddr_.addr_in();
    while(1){
        int ret = ::connect(clientfd_, (sockaddr*)&addr, sizeof(sockaddr_in));
        if(ret == 0){
            std::cout<<"connect to server successfully."<<std::endl;
            break;
        }else if(ret == -1){
            if(errno == EINTR){
                continue;
            }else if(errno == EINPROGRESS){
                break;
            }else{
                perror("TcpClient::connect()");
                return;
            }
        }
    }

    fd_set writeset;
    FD_ZERO(&writeset);
    FD_SET(clientfd_, &writeset);

    struct timeval tv;
    tv.tv_sec = 3;
    tv.tv_usec = 0;
    if(select(clientfd_ + 1, NULL, &writeset, NULL, &tv) == -1){
         std::cout<<"connect to server error"<<std::endl;
    }
    int err;
    socklen_t len = static_cast<socklen_t>(sizeof err);
    if(::getsockopt(clientfd_, SOL_SOCKET, SO_ERROR, &err, &len) < 0){
        perror("TcpClient::connect()");
        return;
    }

    if(err == 0)
        std::cout<<"connect to server successfuly."<<std::endl;
    else
        std::cout<<"connect to server error."<<std::endl;
    
    conn->writeString("I'm client");
    loop_->loop();

}

void TcpClient::readCallBack(std::shared_ptr<TcpConnection> conn){
    
}

void TcpClient::writeCallBack(std::shared_ptr<TcpConnection> conn){
    //conn->writeString("I'm client\n");
}