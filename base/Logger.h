#pragma once
#include<map>

#include<vector>
#include<string>
#include<unordered_map>

#include"Outputer.h"

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
    void log(LogLevel level, const std::string &message);

private:
    std::vector<OutputerPtr> outputers_;
    LogLevel logLevel_;

    std::unordered_map<LogLevel, std::string> logLevelStr_;
};