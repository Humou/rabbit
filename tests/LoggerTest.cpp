#include"LoggerTest.h"
#include"Logger.h"
void LoggerTest(){
     Logger logger;
     OutputerPtr out = std::make_shared<Outputer>("./logger.txt");
     logger.addOutputer(out);

     logger.log(LogLevel::DEBUG, "first log");
     logger.log(LogLevel::DEBUG, "second log");
     logger.log(LogLevel::DEBUG, "third log");
}