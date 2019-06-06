#pragma once
#include<string>
#include<memory>

class Outputer{
public:
    //Outputer(int fd);
    Outputer(const std::string& filename);
    ~Outputer();

    void output(const std::string& log);
private:
    int fd_;
};

using OutputerPtr = std::shared_ptr<Outputer>;