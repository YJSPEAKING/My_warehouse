//能够得到孤儿进程
#include <func.h>
int main()
{
    pid_t pid;
    pid=fork();
    if(pid==0)
    {
        while(1);
        return 0;
    }
    else
    {
        sleep(1);
        return 0;
    }
}