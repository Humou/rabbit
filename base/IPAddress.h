#ifndef IPADDRESS_H
#define IPADDRESS_H

#include<string>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>

class IPAddress{
public:
    IPAddress(unsigned long ip, unsigned short port);
    IPAddress(const std::string &ip, unsigned short port);
    std::string IpPortString();
    sockaddr_in addr_in() const{ return addr_in_;}
private:
  uint16_t port_;
  uint32_t ip_;  

  sockaddr_in addr_in_;
};

#endif //IPADDRESS_H