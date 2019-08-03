#include"HttpRequest.h"
#include"../net/Buffer.h"
#include"../net/EventHandler.h"

enum class ParseState{
    RequestLine,
    RequestHeaders,
    ReuqestBody,
    GotAll,
};

class HttpResponse;
class HttpHandler : public EventHandler{
public:
    HttpHandler(int fd, std::shared_ptr<EventLoop> &loop);

    void handleRead() override;
    void handleWrite() override;
    HttpResponse handleRequest();

    bool processRequestLine(const char* begin, const char* end);
    bool parseRequest(Buffer* buf);
    std::string contents();
private:
    Buffer inputBuffer_;
    Buffer outPutBuffer_;

    HttpRequest request_;
    ParseState parseState_;
};
