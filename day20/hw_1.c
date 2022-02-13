//通过fork创建子进程，让父子进程都打印pid，都处于while(1),然后用ps进程查看，查看完毕，用kill命令杀掉
#include <func.h>
int main()
{
    pid_t pid;
    pid=fork();
    if(pid==0)
    {
        printf("子进程的pid=%d\n",getpid());
        while(1);
        return 0;
    }
    else
    {
        printf("父进程的pid=%d\n",getpid());
        sleep(1);
        while(1);
        return 0;
    }
}