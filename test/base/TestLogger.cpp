#include "base/Logger.h"
#include <unistd.h>
#include <iostream>
#include <vector>
#include <memory>
#include <fstream>
#include "base/Thread.h"
#include <assert.h>
#include "stdio.h"

int file_line_size()
{
    std::ifstream in;
    in.open(Logger::getLogFileName());
    char buf[1024];
    int count = 0;
    while(in.getline(buf, 1024)){
    	count++;
    }
    in.close();
    return count;
}

void threadFunc()
{
    for (int i = 0; i < 100000; ++i)
    {
        LOGInfo << i;
    }
}

void type_test()
{
    std::cout << "----------type test-----------" << std::endl;
    LOGInfo << 0;
    LOGInfo << 1234567890123;
    LOGInfo << 1.0f;
    LOGInfo << 3.1415926;
    LOGInfo << (short) 1;
    LOGInfo << (long long) 1;
    LOGInfo << (unsigned int) 1;
    LOGInfo << (unsigned long) 1;
    LOGInfo << (long double) 1.6555556;
    LOGInfo << (unsigned long long) 1;
    LOGInfo << 'c';
    LOGInfo << "abcdefg";
    LOGInfo << std::string("This is a string");
    LOGInfo << "fddsa" << 'c' << 0 << 3.666 << std::string("This is a string");
    sleep(3);
    assert(file_line_size() == 14);
    std::cout << "----------type test success!-----------" << std::endl;
}

void level_test()
{
    std::cout << "----------level test-----------" << std::endl;
    LOGInfo << 0;
    LOGDebug << 1234567890123;
    LOGWarning << 1.0f;
    LOGError << 3.1415926;
    LOGInfo << (short) 1;

    Logger::setMinOutputLevel_(LogLevel::WARNING);
    LOGInfo << (long long) 1;
    LOGDebug << (unsigned int) 1;
    LOGWarning << (unsigned long) 1;
    LOGError << (long double) 1.6555556;

    Logger::setMinOutputLevel_(LogLevel::ERROR);
    LOGInfo << (unsigned long long) 1;
    LOGInfo << 'c';
    LOGInfo << "abcdefg";
    LOGInfo << std::string("This is a string");
    LOGInfo << "fddsa" << 'c' << 0 << 3.666 << std::string("This is a string");
    
    Logger::setMinOutputLevel_(LogLevel::INFO);
    sleep(3);
    
    assert(file_line_size() == 20);
    std::cout << "----------level test success!-----------" << std::endl;
}

void stressing_single_thread()
{
    std::cout << "----------stressing test single thread-----------" << std::endl;
    for (int i = 0; i < 100000; ++i)
    {
        LOGInfo << i;
    }
    sleep(3);
    std::cout << "----------stressing test single thread success!-----------" << std::endl;
    assert(file_line_size() == 100020);
}

void stressing_multi_threads(int threadNum = 4)
{
    std::cout << "----------stressing test multi thread-----------" << std::endl;
    std::vector<std::shared_ptr<Thread>> vsp;
    for (int i = 0; i < threadNum; ++i)
    {
        std::shared_ptr<Thread> tmp(new Thread(threadFunc, "testFunc"));
        vsp.push_back(tmp);
    }
    for (int i = 0; i < threadNum; ++i)
    {
        vsp[i]->start();
    }
    sleep(12);
    assert(file_line_size() == 500020);
    std::cout << "----------stressing test multi thread success!-----------" << std::endl;
}

int main()
{
    remove(Logger::getLogFileName().c_str());
    // 14 lines
    type_test();

    // 6 lines
    level_test();

    // 100000 lines
    stressing_single_thread();

    // 400000 lines
    stressing_multi_threads();
    return 0;
}