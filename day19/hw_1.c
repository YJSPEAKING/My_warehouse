#include <func.h>
//将标准输出重定向到log1文件
//使用dup2
int main(int argc,char* argv[])
{
    ARGS_CHECK(argc,2);
    int fd=open(argv[1],O_RDWR|O_CREAT,0666);
    ERROR_CHECK(fd,-1,"open");
    printf("\n");
    int fd1=dup2(fd,STDOUT_FILENO);
    printf("Writing instead of Printing\n");
    close(fd);
    close(fd1);
    return 0;
}