#ifndef BUFFER_H
#define BUFFER_H

#include<algorithm>
#include<vector>

#include<assert.h>
#include<string>

class Buffer{
public:
    static const size_t KCheapPrepend = 8;
    static const size_t KInitialSize = 1024;

    Buffer()
    : buffer_(KCheapPrepend + KInitialSize),
      readerIndex_(KCheapPrepend),
      writerIndex_(KCheapPrepend)
      {
        
      }

      void swap(Buffer& rhs){
          buffer_.swap(rhs.buffer_);
          std::swap(readerIndex_, rhs.readerIndex_);
          std::swap(writerIndex_, rhs.writerIndex_);
      }

      size_t readableBytes() const{
          return writerIndex_ - readerIndex_;
      }

      size_t writableBytes() const{
          return buffer_.size() - writerIndex_;
      }

      size_t prependableBytes() const{
          return readerIndex_;
      }

      const char* peek() const{
          return begin() + readerIndex_;
      }

      const char* findCRLF() const{
          const char* crlf = std::search(peek(), beginWrite(), KCRLF, KCRLF + 2);
          return crlf == beginWrite() ? NULL : crlf;
      }

      const char* findCRLF(const char* start) const{
          assert(peek() <= start);
          assert(start <= beginWrite());
          const char* crlf = std::search(start, beginWrite(), KCRLF, KCRLF + 2);
          return crlf == beginWrite()?NULL:crlf;
      }

      void retrieve(size_t len){
          assert(len <= readableBytes());
          if(len < readableBytes()){
              readerIndex_ += len;
          }
          else{
              retrieveAll();
          }
      }

      void retrieveUntil(const char* end){
          assert(peek() <= end);
          assert(end <= beginWrite());
          retrieve(end - peek());
      }

      void retrieveInt32(){
          retrieve(sizeof(int32_t));
      }

      void retrieveInt16(){
          retrieve(sizeof(int16_t));
      }

      void retrieveInt8(){
          retrieve(sizeof(int8_t));
      }

      void retrieveAll(){
          readerIndex_ = KCheapPrepend;
          writerIndex_ = KCheapPrepend;
      }

      std::string retrieveAllASString(){
        return retrieveAsString(readableBytes());
      }

      std::string retrieveAsString(size_t len){
          assert(len <= readableBytes());
          std::string result(peek(), len);
          retrieve(len);
          return result;
      }

    void append(const char* data, size_t len){
        ensureWritableBytes(len);
        std::copy(data, data + len, beginWrite());
        hasWritten(len);
    }

    void append(const void *data, size_t len){
        append(static_cast<const char*>(data), len);
    }

    void ensureWritableBytes(size_t len){
        if(writableBytes() < len){
            makeSpace(len);
        }
        assert(writableBytes() >= len);
    }

    char* beginWrite(){
        return begin() + writerIndex_;
    }

    const char* beginWrite() const{
        return begin() + writerIndex_;
    }

    void hasWritten(size_t len){
        writerIndex_ += len;
    }

    
    void  appendInt8(int8_t x){
        append(&x, sizeof x);
    }

    void shrink(size_t reserve){
        Buffer other;
        other.ensureWritableBytes(readableBytes() + reserve);
        //other.append(to)
    }

    ssize_t readFd(int fd, int* savedErrno);
private:
    char* begin(){
        return &*buffer_.begin();
    }    

    const char* begin() const{
        return &*buffer_.begin();
    }

    void makeSpace(size_t len){
        if(writableBytes() + prependableBytes() < len + KCheapPrepend){
            buffer_.resize(writerIndex_ + len);
        }
        else{
            assert(KCheapPrepend < readerIndex_);
            size_t readable = readableBytes();
            std::copy(begin() + readerIndex_, begin() + writerIndex_, begin() + KCheapPrepend);
            readerIndex_ = KCheapPrepend;
            writerIndex_ = readerIndex_ + readable;
            assert(readable == readableBytes());
        }

    }

private:
    std::vector<char> buffer_;
    size_t readerIndex_;
    size_t writerIndex_;

    static const char KCRLF[];
};
#endif