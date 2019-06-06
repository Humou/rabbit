#include<sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include"Outputer.h"
 Outputer::Outputer(const std::string& filename){
     fd_ = open(filename.c_str(), O_APPEND|O_CREAT|O_WRONLY|O_CLOEXEC, S_IRUSR|S_IWUSR| S_IRGRP| S_IROTH);
     if(fd_ == -1){
         perror("Outputer(const std::string& filename): open file failed");
         return;
     }
 }
Outputer::~Outputer(){

}
 void Outputer::output(const std::string& log){
     int rt = ::write(fd_, log.c_str(), log.size());
     if(rt == -1){
         perror("Outputer::output(const std::string& log): write failed");
         return;
     }
 }