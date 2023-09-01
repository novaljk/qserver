#include "base/FileUtil.h"
#include <cstdio>
#include <cassert>  

AppendFile::AppendFile(std::string filename){
    fp_ = fopen(filename.c_str(), "ae");
    assert(fp_ != nullptr);
    setbuffer(fp_, buffer_, sizeof(buffer_));
}

void AppendFile::append(const char *line, const size_t len){
    size_t n = write(line, len);
    // 循环写入文件
    while(len - n > 0){
        size_t x = write(line + n, len - n);
        if (x == 0) {
            int err = ferror(fp_);
            if (err){
                fprintf(stderr, "AppendFile::append() failed !\n");
            } 
            break;
        }
        n += x;
    }
}

void AppendFile::flush(){
    fflush(fp_);    
}

size_t AppendFile::write(const char *line, const size_t len){
    // fwrite 的线程不安全版本
    return fwrite_unlocked(line, 1, len, fp_);
}