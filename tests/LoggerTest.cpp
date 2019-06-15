#include"LoggerTest.h"
#include"Logger.h"
void LoggerTest(){

    Log(LogLevel::DEBUG, "first log");
    Log(LogLevel::DEBUG, "second log");
    Log(LogLevel::DEBUG, "third log");
}