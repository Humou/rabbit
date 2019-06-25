#pragma once
#include<unordered_map>
enum class ResponseCode{
    OK = 200,
    BadRequest = 400,
    NotFound = 404,
};

enum class HttpVersion{
    VERSION_1_0,
    VERSION_1_1
};

struct HttpResponse{
public:
    HttpResponse();

    void set_responseCode(ResponseCode code){code_ = code;}
    ResponseCode responseCode(){return code_;}

    void set_header(const std::string &key, const std::string &value){headers_[key] = value;}
    

    void set_keekAlive(bool on){keepAlive_ = on;}
    
    void set_contents(const std::string &contents){contents_ = contents;}

    std::string message();
private:
    ResponseCode code_;
    std::unordered_map<std::string, std::string> headers_;
    std::string statusMessage_;
    bool keepAlive_;
    std::string contents_;
    HttpVersion version_;
};