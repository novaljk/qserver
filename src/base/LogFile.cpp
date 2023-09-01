#include "base/LogFile.h"

LogFile::LogFile(const std::string& basename, int flushEveryN):
    basename_(basename), flushEveryN_(flushEveryN), count_(0),
    file_(std::make_unique<AppendFile>(basename)){
}

void LogFile::append(const char* logline, int len){
    MutexLockGuard guard(mutex_);
    append_unlocked(logline, len);
}

void LogFile::flush(){
    MutexLockGuard guard(mutex_);
    file_->flush();
}
bool LogFile::rollFile(){
    return false;
}

void LogFile::append_unlocked(const char* logline, int len){
    file_->append(logline, len);
    count_++;
    if(count_ >= flushEveryN_){
        count_ = 0;
        file_->flush();
    }
}