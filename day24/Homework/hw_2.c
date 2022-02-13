//通过sigaction，打印发送信号的发送者的pid和uid
#include<func.h>

void func(int signum,siginfo_t *p,void *p1)
{
    printf("signal %d has been intercepted\n",signum);
    printf("pid of the sender is:%d,uid of the sender is:%d\n",p->si_pid,p->si_uid);
    sleep(5);
    printf("signal %d's func is over\n",signum);
}

int main()
{
    struct sigaction act;
    bzero(&act,sizeof(act));
    act.sa_flags=SA_SIGINFO;
    act.sa_sigaction=func;
    sigaction(SIGINT,&act,NULL);
    while(1);
    return 0;
}