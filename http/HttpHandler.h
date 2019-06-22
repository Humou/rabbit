#include"HttpRequest.h"
#include"../net/EventHandler.h"

class HttpHandler : public EventHandler{
public:
    HttpHandler(int fd, uint32_t events, std::shared_ptr<EventLoop> &loop);

    void handleRead() override;
    void handleWrite() override;

private:
    //HttpRequest httpReq_;
};
