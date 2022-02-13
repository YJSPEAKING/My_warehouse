//通过fork创建子进程，然后父进程通过wait回收，同时拿到子进程的返回值
#include <func.h>
int main()
{
    pid_t pid;
    pid=fork();
    if(pid==0)
    {
        return 5;
    }
    else
    {
        int status;
        pid=wait(&status);
        if(WIFEXITED(status))
        {
            printf("child exit code=%d\n",WEXITSTATUS(status));
        }
        else
        {
            printf("child crush\n");
        }
        printf("wait pid=%d\n",pid);
        return 0;
    }
}