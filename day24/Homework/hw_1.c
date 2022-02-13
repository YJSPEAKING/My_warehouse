//sigaction实现2号信号，屏蔽3号信号的执行效果，同时在2号信号的信号处理流程中，判断3号信号是否被挂起
#include<func.h>

void func(int signum,siginfo_t *p,void *p1)
{
    printf("signal %d has been intercepted\n",signum);
    sleep(5);
    sigset_t(set);
    sigpending(&set);
    if(sigismember(&set,SIGQUIT))
    {
        printf("SIGQUIT is pending\n");
    }
    else{
        printf("no pending\n");
    }
    printf("signal %d's func is over\n",signum);
}

int main()
{
    struct sigaction act;
    bzero(&act,sizeof(act));
    act.sa_flags=SA_SIGINFO;
    act.sa_sigaction=func;
    sigemptyset(&act.sa_mask);
    sigaddset(&act.sa_mask,SIGQUIT);
    sigaction(SIGINT,&act,NULL);
    while(1);
    return 0;
}