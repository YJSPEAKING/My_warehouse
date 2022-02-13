//sigaction实现信号不断重入的执行效果(来回打断的效果)
#include<func.h>

void func(int signum, siginfo_t *p,void *p1)
{
    printf("signal %d has been intercepted\n",signum);
    sleep(5);
    printf("signal %d's func is over\n",signum);
}
int main()
{
    int ret;
    struct sigaction act;
    bzero(&act,sizeof(act));
    act.sa_flags=SA_SIGINFO|SA_NODEFER;
    act.sa_sigaction=func;
    ret=sigaction(SIGINT,&act,NULL);
    ERROR_CHECK(ret,-1,"sigaction1")
    ret=sigaction(SIGQUIT,&act,NULL);
    ERROR_CHECK(ret,-1,"sigaction2")
    while(1);
    return 0;
}