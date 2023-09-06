#include "base/Thread.h"
#include "base/CountDownLatch.h"
#include <assert.h>
#include <unistd.h>
#include <iostream>
#include "base/CurrentThread.h"

CountDownLatch latch(2);

void loop1(){
    latch.wait();
    for(int i = 1; i < 10; i++){
        sleep(1);
        std::cout<< CurrentThread::t_cachedTid << " " << i << std::endl;
    }
}

void loop2(){
    for(int i = 1; i < 10; i++){
        sleep(2);
        std::cout<< CurrentThread::t_cachedTid << " " << i * 100 << std::endl;
    }
    latch.countDown();
}

void loop3(){
    for(int i = 1; i < 10; i++){
        sleep(3);
        std::cout<< CurrentThread::t_cachedTid << " " << i * 10 << std::endl;
    }
    latch.countDown();
}

int main(){
    std::function<void()> func1(loop1);
    std::function<void()> func2(loop2);
    std::function<void()> func3(loop3);
    Thread thread1(func1);
    Thread thread2(func2);
    Thread thread3(func3);
    thread1.start();
    thread2.start();
    thread3.start();
    for(int i = 1; i <= 3; i++){
        std::cout<< "Term start."<< std::endl;
        sleep(10);
    }
}