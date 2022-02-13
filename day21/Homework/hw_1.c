#include<func.h>

int main()
{
    int fd=open("/tmp/log",O_RDWR|O_CREAT,0666);
    ERROR_CHECK(fd,-1,"open")
    if(fork())
    {
        exit(0);//父进程退出
    }
    setsid();//子进程创建新会话，走向人生巅峰
    chdir("/");//设置工作目录为根目录
    umask(0);//设置掩码
    int i;
    for(i=0;i<3;i++)
    {
        close(i);//其他无关的文件全部关掉
    }
    while(1)
    {
        write(fd,"wohenshuai",10);
        sleep(2);
    }
}