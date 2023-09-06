#pragma once
#include "base/Condition.h"
#include "base/MutexLock.h"
#include "base/noncopyable.h"

// CountDownLatch 倒计时锁存器, 基于条件变量
class CountDownLatch : noncopyable {
 public:
  explicit CountDownLatch(int count);
  void wait();
  void countDown();

 private:
  mutable MutexLock mutex_;
  Condition condition_;
  int count_;
};