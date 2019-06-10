#pragma once
#include<map>

#include<vector>
#include<string>
#include<unordered_map>

#include"Outputer.h"

#define Log(level, ...)                                                             \
        do{                                                                         \
          Logger::getLogger().log(level, __FILE__, __LINE__, __func__, __VA_ARGS__);\
        }while(0)                                                                   \

struct LogEnty{
    int line_;
    std::string filename_;    
};

enum class LogLevel{
    ALL, WARN, INFO, DEBUG, ERROR, FATAL
};


class Logger{
public:
    Logger();
    ~Logger();

    void addOutputer(OutputerPtr &outputer);
    void removeOutputer(OutputerPtr &outputer);
    //void log(LogLevel level, const std::string &message);
    void log(LogLevel level, const char *file, int line, const char *func, const char* message);
    static Logger& getLogger();

private:
    void mayRotate();
private:
    std::vector<OutputerPtr> outputers_;
    LogLevel logLevel_;

    std::unordered_map<LogLevel, std::string> logLevelStr_;
    std::string filename_;
    int fd_ = -1;

    int lastRotate_;
    static const int KSecond;
};