#include "base/Thread.h"
#include <assert.h>
#include <unistd.h>
#include <iostream>

void loop1(){
    for(int i = 0; i < 10; i++){
        sleep(1);
        std::cout<< i << std::endl;
    }
}

void loop2(){
    for(int i = 0; i < 10; i++){
        sleep(2);
        std::cout<< i * 100 << std::endl;
    }
}

int main(){
    std::function<void()> func1(loop1);
    std::function<void()> func2(loop2);
    Thread thread1(func1);
    Thread thread2(func2);
    thread1.start();
    thread2.start();
    while(true){
        std::cout<< "Term start."<< std::endl;
        sleep(10);
    }
}