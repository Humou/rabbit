#pragma once
struct HttpResponse{
public:
    const std::string& message() const{return message_;}
    void set_message(const std::string &message){message_ = message;}
private:
    std::string message_;
};