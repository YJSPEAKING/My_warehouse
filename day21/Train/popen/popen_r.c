#include <func.h>
//popen以r状态拉起进程，fp是管道的读端
//新进程的标准输出会被重定向到管道的写端→popen用到了dup
//popen是一个库函数，里面有一个系统调用
int main()
{
    FILE *fp;
    //popen进程会启动(先fork再exec)一个新进程
    //popen进程和新进程间有一条无名管道
    //以r方式打开，返回的就是读端，读到是新进程的标准输出
    fp=popen("ls -l","r");
    char buf[1024]={0};
    fread(buf,1,sizeof(buf),fp);
    printf("%s",buf);
    pclose(fp);
    return 0;
}