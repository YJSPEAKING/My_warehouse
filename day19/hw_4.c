#include <func.h>
int main(int argc,char* argv[])
{
    ARGS_CHECK(argc,2);
    int fd=open(argv[1],O_RDWR|O_CREAT);
    ERROR_CHECK(fd,-1,"open");
    int ret=write(fd,"hello",5);
    ERROR_CHECK(ret,-1,"write");
    close(fd);
    return 0;
}