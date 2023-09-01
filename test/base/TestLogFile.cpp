#include "base/LogFile.h"
#include <cstring>
#include <ctime>
#include <cstdlib>
#include <unistd.h>
#include <assert.h>

char *randstr(char *str, const int len)
{
    assert(len >= 2);
    int i;
    for (i = 0; i < len - 2; ++i)
    {
        switch ((rand() % 3))
        {
        case 1:
            str[i] = 'A' + rand() % 26;
            break;
        case 2:
            str[i] = 'a' + rand() % 26;
            break;
        default:
            str[i] = '0' + rand() % 10;
            break;
        }
    }
    str[len - 2] = '\n';
    str[len - 1] = '\0';
    return str;
}

int main(){
    srand(time(NULL));
    LogFile file("test.log");
    for(int i = 0; i < 1024; i++){
        char line[16];
        randstr(line, 16);
        file.append(line, strlen(line));       
    }
    sleep(5);   
}