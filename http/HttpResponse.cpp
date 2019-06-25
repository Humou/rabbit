 #include"HttpResponse.h"

 HttpResponse::HttpResponse()
    : code_(ResponseCode::NotFound), version_(HttpVersion::VERSION_1_0),keepAlive_(false),
      statusMessage_("not found")
 {

 }
 std::string HttpResponse::message(){
    std::string msg;
    if(code_ == ResponseCode::OK){
        statusMessage_ = "ok";
    }
    if(version_ == HttpVersion::VERSION_1_0){
        msg += "HTTP/1.0 " + std::to_string(int(code_)) + " ";
        msg += statusMessage_ + "\r\n";
    }
    else{
        msg += "HTTP/1.1 " + std::to_string(int(code_)) + " ";
        msg += statusMessage_ + "\r\n";
    }
    msg += "Content-Length: " + std::to_string(contents_.size()) + "\r\n";
    if(keepAlive_){
        msg += "Connection: Keep-Alive\r\n";
    }

    else{
        msg += "Connection: close\r\n";
    }

    for(auto &p : headers_){
        msg += p.first + ": " + p.second + "\r\n";
    }

    msg += "\r\n";
    msg += contents_;
    return msg;
 }