#include<ctime>
#include<sstream>

#include"Logger.h"

Logger::Logger()
{
    logLevelStr_.insert({LogLevel::ALL, "ALL"});
    logLevelStr_.insert({LogLevel::WARN, "WARN"});
    logLevelStr_.insert({LogLevel::INFO, "INFO"});
    logLevelStr_.insert({LogLevel::DEBUG, "DEBUG"});
    logLevelStr_.insert({LogLevel::ERROR, "ERROR"});
    logLevelStr_.insert({LogLevel::FATAL, "FATAL"});
}

Logger::~Logger(){

}
void Logger::addOutputer(OutputerPtr &outputer){
    outputers_.push_back(outputer);
}

void Logger::removeOutputer(OutputerPtr &outputer){
    //outputers_.erase(outputer);
}

 void Logger::log(LogLevel level, const std::string &message){
     std::stringstream out;
     out<<logLevelStr_[level]<<": "<<message<<" file: "<<__FILE__<<" line: "<<__LINE__;

    time_t now;
    struct tm *fmt;

    time(&now);
    fmt = localtime(&now);
    out<<" date: "<<fmt->tm_year + 1900<<" "<<fmt->tm_mon + 1<<" "<<fmt->tm_mday<<" ";
    out<<fmt->tm_hour<<":"<<fmt->tm_min<<":"<<fmt->tm_sec<<"\n";

    std::string logStr = out.str();
    for(auto &outputer : outputers_){
        if(outputer) outputer->output(logStr);
    }
 }


