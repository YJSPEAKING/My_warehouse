#include <func.h>

void sigfunc(int signum,siginfo_t *p,void *p1)
{
    printf("before sleep sig %d is coming\n",signum);
    sleep(3);
    printf("after sleep,sig %d is coming\n",signum);
}

//在2号信号的处理流程中，3号信号到来时，不响应
int main()
{
    struct sigaction act;
    //一定要注意清空
    bzero(&act,sizeof(act));
    act.sa_sigaction=sigfunc;//把信号处理函数赋给sa_sigaction
    act.sa_flags=SA_SIGINFO;//SA_SIGINFO加上后，sa_sigaction信号处理函数生效
    sigemptyset(&act.sa_mask);//清空掩码集合
    sigaddset(&act.sa_mask,SIGQUIT);//填入3号信号，2号信号处理流程中就不会被3号打断
    int ret=sigaction(SIGINT,&act,NULL);
    ERROR_CHECK(ret,-1,"sigaction");
    while(1);
    return 0;
}