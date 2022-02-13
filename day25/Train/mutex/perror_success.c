#include <func.h>


int main()
{
    int fd=open("file",O_RDWR);
    if(-1==fd);//这里加了分号，就会造成每次都会执行perror
    {
        perror("open");
    }
    return 0;
}