 #include"Buffer.h"

#include<errno.h>
#include<sys/uio.h>
#include <unistd.h>

const char Buffer::KCRLF[] = "\r\n";
const size_t Buffer::KCheapPrepend;
const size_t Buffer::KInitialSize;

 ssize_t Buffer::readFd(int fd, int* savedErrno){
     //char extrabuf[6536];
     //struct iovec vec[2];
     //const size_t writable = writableBytes();
     //vec[0].iov_base = begin() + writerIndex_;
     //vec[0].iov_len = writable;
     //vec[1].iov_base = extrabuf;
     //vec[1].iov_len = sizeof extrabuf;
     //const ssize_t n = 
     char buf[4096];
     int ret = ::read(fd, buf, sizeof buf);
     if(ret == -1){
         if(savedErrno) *savedErrno = errno;
         return -1;
     }
     
    append(buf, ret);
    return ret;
 }

 ssize_t Buffer::writeFd(int fd, int* savedErrno){
     int len = readableBytes();
     int ret = ::write(fd, buffer_.data() + readerIndex_, len);
     if(ret == -1){
         if(savedErrno) *savedErrno = errno;
         return -1;
     }
     
     readerIndex_ += ret;

    return ret;
 }

