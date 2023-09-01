#pragma once
#include <memory>
#include <string>
#include "base/FileUtil.h"
#include "base/MutexLock.h"
#include "base/noncopyable.h"


// TODO: 实现线程安全，并提供自动归档功能
class LogFile : noncopyable {
 public:
  // 每被append flushEveryN次，flush一下，会往文件写，只不过，文件也是带缓冲区的
  explicit LogFile(const std::string& basename, int flushEveryN = 1024);
  ~LogFile() = default;

  void append(const char* logline, int len);
  void flush();
  bool rollFile();

 private:
  void append_unlocked(const char* logline, int len);

  const std::string basename_;
  const int flushEveryN_;

  int count_;
  MutexLock mutex_;
  std::unique_ptr<AppendFile> file_;
};