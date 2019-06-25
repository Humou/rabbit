#include<ctime>
#include<sstream>
#include<sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include"Logger.h"
const int Logger::KSecond = 4 * 60 * 60;    //four hour 
Logger::Logger()
{
    logLevelStr_.insert({LogLevel::ALL, "ALL"});
    logLevelStr_.insert({LogLevel::WARN, "WARN"});
    logLevelStr_.insert({LogLevel::INFO, "INFO"});
    logLevelStr_.insert({LogLevel::DEBUG, "DEBUG"});
    logLevelStr_.insert({LogLevel::ERROR, "ERROR"});
    logLevelStr_.insert({LogLevel::FATAL, "FATAL"});

    time_t now;
    time(&now);
    lastRotate_ = now;
    struct tm *fmt;   
    fmt = localtime(&now);

    std::stringstream out;
    int year = fmt->tm_year + 1900, month = fmt->tm_mon + 1, day = fmt->tm_mday;
    int hour = fmt->tm_hour, min = fmt->tm_min, sec = fmt->tm_sec;
    out<<year<<month<<day<<" "<<hour<<":"<<min<<":"<<sec<<" ";

    filename_ = "rabbit_" + out.str();
    fd_ = open(filename_.c_str(), O_APPEND|O_CREAT|O_WRONLY|O_CLOEXEC, S_IRUSR|S_IWUSR| S_IRGRP| S_IROTH);
    if(fd_ == -1){
        perror("Logger::mayOpenFile(): open file failed");
        return;
    }
}

Logger::~Logger(){

}
void Logger::addOutputer(OutputerPtr &outputer){
    outputers_.push_back(outputer);
}

void Logger::removeOutputer(OutputerPtr &outputer){
    //outputers_.erase(outputer);
}
/*
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
*/
void Logger::log(LogLevel level, const char *file, int line, const char *func, const char* message){
    std::stringstream out;
    time_t now;
    struct tm *fmt;

    time(&now);
    fmt = localtime(&now);
    int year = fmt->tm_year + 1900, month = fmt->tm_mon + 1, day = fmt->tm_mday;
    int hour = fmt->tm_hour, min = fmt->tm_min, sec = fmt->tm_sec;
    out<<logLevelStr_[level]<<" ";
    out<<message<<" ";
    out<<year<<month<<day<<" "<<hour<<":"<<min<<":"<<sec<<" ";
    out<<file<<":"<<line<<" "<<func<<"\n";   
    std::string logStr = out.str();

    mayRotate();
    int ret = ::write(fd_, logStr.c_str(), logStr.size());
    if(ret == -1){
        perror("Logger::log(LogLevel level, const char *file, int line, char *func, const char* message)");
        return;
    }
}

Logger& Logger::getLogger(){
    static Logger logger;
    return logger;
}

void Logger::mayRotate(){
    time_t now;
    time(&now);
    
    if((now - lastRotate_) < KSecond) return;

    lastRotate_ = now;
    struct tm *fmt;   
    fmt = localtime(&now);

    std::stringstream out;
    int year = fmt->tm_year + 1900, month = fmt->tm_mon + 1, day = fmt->tm_mday;
    int hour = fmt->tm_hour, min = fmt->tm_min, sec = fmt->tm_sec;
    out<<year<<month<<day<<" "<<hour<<":"<<min<<":"<<sec<<" ";

    filename_ = "rabbit_" + out.str();
    int fd = open(filename_.c_str(), O_APPEND|O_CREAT|O_WRONLY|O_CLOEXEC, S_IRUSR|S_IWUSR| S_IRGRP| S_IROTH);
    if(fd == -1){
        perror("Logger::mayOpenFile(): open file failed");
        return;
    }
    dup2(fd_, fd);
    close(fd);
}