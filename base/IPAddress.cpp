 #include"IPAddress.h"

 IPAddress::IPAddress(unsigned long ip, unsigned short port)
        :ip_(ip), port_(port)
        {
          addr_in_.sin_family = AF_INET;
          addr_in_.sin_port = htons(port_);
          addr_in_.sin_addr.s_addr = htonl(ip_);

        }

 std::string IPAddress::IpPortString(){
     char *ip = new char[INET_ADDRSTRLEN];
     uint32_t ip_n = htonl(ip_);

     if(inet_ntop(AF_INET, static_cast<void*>(&ip_n), ip, INET_ADDRSTRLEN) == NULL){
         perror("IPAddress::IpPortString");
         exit(1);
     }
     return std::string(ip) + ": " + std::to_string(port_);
 }