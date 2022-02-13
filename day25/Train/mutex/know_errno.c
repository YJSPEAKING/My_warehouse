#include <func.h>

//打开一个文件不存在
//通过errno去得到对应的宏，然后到man帮助中去搜索对应的宏
int main()
{
    int fd=open("file",O_RDWR);
    ERROR_CHECK(fd,-1,"open");
    return 0;
}