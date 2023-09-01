#pragma once
#include <string>
#include "base/noncopyable.h"

class AppendFile : noncopyable {
 public:
  explicit AppendFile(std::string filename);
  ~AppendFile()=default;
  // append 向文件写
  void append(const char *line, const size_t len);
  void flush();

 private:
  size_t write(const char *line, const size_t len);
  FILE *fp_;
  char buffer_[64 * 1024];
};