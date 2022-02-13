//通过fork创建进程，能够产生僵尸进程
#include <func.h>
int main()
{
    pid_t pid;
    pid=fork();
    if(pid==0)
    {
        return 0;
    }
    else
    {
        while(1);
        return 0;
    }
}