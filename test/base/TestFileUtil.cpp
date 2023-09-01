#include "base/FileUtil.h"
#include <cstring>

int main(){
    AppendFile file("test.log");
    const char* line1 = "abc123\n";
    const char* line2 = "mytest\n";
    file.append(line1, strlen(line1));
    file.flush();
    file.append(line2, strlen(line2));
}