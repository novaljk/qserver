#include "base/AsyncLogging.h"
#include <iostream>
#include <unistd.h>
AsyncLogging logger("test.log");

void TestCase1(){
    for(int i = 0; i < 1000000; i++){
        char str[128];
        snprintf(str, 128, "Test log-%d: hello async.\n", i);
        logger.append(str, strlen(str));
    }
}

int main(){
    logger.start();
    TestCase1();
    sleep(10);
}