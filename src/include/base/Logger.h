#pragma once
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include "base/LogStream.h"

class AsyncLogging;

enum class LogLevel{
    UNKNOWN = 0,
    DEBUG      ,
    INFO       ,
    WARNING    ,
    ERROR 
};

class Logger {
 public:
  Logger(const char *fileName, int line, LogLevel level);
  ~Logger(){};
  LogStream &stream() { return impl_.stream_; }
  static void setLogFileName(std::string fileName) { logFileName_ = fileName; }
  static std::string getLogFileName() { return logFileName_; }
  static void setMinOutputLevel_(LogLevel level) { minOutputLevel_ = level; }
  static LogLevel getMinOutputLevel_() { return minOutputLevel_; }

 private:
  class Impl {
   public:
    Impl(const char *fileName, int line, LogLevel level);
    ~Impl();
    void formatTime();
    LogStream stream_;
    int line_;
    std::string basename_;
    LogLevel level_;
  };
  Impl impl_;
  static std::string logFileName_;
  static LogLevel minOutputLevel_;
};

#define LOGDebug Logger(__FILE__, __LINE__, LogLevel::DEBUG).stream()
#define LOGInfo Logger(__FILE__, __LINE__, LogLevel::INFO).stream()
#define LOGWarning Logger(__FILE__, __LINE__, LogLevel::WARNING).stream()
#define LOGError Logger(__FILE__, __LINE__, LogLevel::ERROR).stream()