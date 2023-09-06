#include "base/Logger.h"
#include <time.h>  
#include <sys/time.h> 
#include "base/AsyncLogging.h"

static pthread_once_t once_control_ = PTHREAD_ONCE_INIT;
static AsyncLogging* logging_;
std::string Logger::logFileName_ = "./WebServer.log";
LogLevel Logger::minOutputLevel_ = LogLevel::INFO;

void once_init(){
    logging_ = new AsyncLogging(Logger::getLogFileName());
    logging_->start();
}

void output(const char* msg, int len)
{
    pthread_once(&once_control_, once_init);
    logging_->append(msg, len);
}

Logger::Logger(const char *fileName, int line, LogLevel level)
  : impl_(fileName, line, level){

}

Logger::Impl::Impl(const char *fileName, int line, LogLevel level)
  : stream_(),
    line_(line),
    basename_(fileName),
    level_(level){
    if(level_ < Logger::getMinOutputLevel_()){
        return;
    }
    switch (level_)
    {
    case LogLevel::DEBUG:   stream_ <<  "[DEBUG] "; break;
    case LogLevel::INFO:    stream_ <<  "[INFO]  "; break;
    case LogLevel::WARNING: stream_ <<  "[WARN]  "; break;
    case LogLevel::ERROR:   stream_ <<  "[ERROR] "; break;
    default: assert(0);
    }
    struct timeval tv;
    time_t time;
    char str_t[26] = {0};
    gettimeofday(&tv, NULL);
    time = tv.tv_sec;
    struct tm* p_time = localtime(&time);   
    strftime(str_t, 26, "%Y-%m-%d %H:%M:%S ", p_time);
    stream_ << str_t;
}

Logger::Impl::~Impl()
{
    if(level_ < Logger::getMinOutputLevel_()){
        return;
    }
    stream_ << " -- " << basename_ << ':' << line_ << '\n';
    const LogStream::Buffer& buf(stream_.buffer());
    output(buf.data(), buf.length());
}
