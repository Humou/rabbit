#include"HttpRequest.h"
#include"../net/Buffer.h"
#include"../net/EventHandler.h"
class HttpResponse;
class HttpHandler : public EventHandler{
public:
    HttpHandler(int fd, std::shared_ptr<EventLoop> &loop);

    void handleRead() override;
    void handleWrite() override;
    HttpResponse handleRequest(const HttpRequest &req);
private:
    Buffer inputBuffer_;
    Buffer outPutBuffer_;
};
