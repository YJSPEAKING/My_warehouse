#include <func.h>

//waitpid 等要等待的子进程
int main()
{
    pid_t pid;
    pid=fork();
    if(0==pid)
    {
        //孩子的代码写这里
        printf("I am child,pid=%d,ppid=%d\n",getpid(),getppid());
        sleep(1);
        exit(3);
    }else{
        //父亲的代码写这里
        printf("I am parent,mychild=%d,pid=%d,ppid=%d\n",pid,getpid(),getppid());
        int status;
        pid_t pid1=waitpid(pid,&status,WNOHANG);//孩子结束以后，会给父亲发送SIGCHLD,可以回收资源
        if(pid1>0)
        {
            if(WIFEXITED(status))//判断子进程是否正常退出
            {
                printf("child exit code=%d\n",WEXITSTATUS(status));
            }else{
                printf("child crash\n");
            }
            printf("wait pid=%d\n",pid1);
        }else{
            printf("no exit child\n");
        }
        return 0;
    }
}