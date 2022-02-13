#include <func.h>

void sigfunc(int signum,siginfo_t *p,void *p1)
{
    printf("before sleep,sig %d is coming\n",signum);
    sleep(3);//模拟让信号处理函数执行一段时间
    printf("after sleep,sig %d is coming\n",signum);
}

//sigaction 基本使用，捕捉2号信号
int main()
{
    struct sigaction act;
    //一定要注意清空
    bzero(&act,sizeof(act));
    act.sa_sigaction=sigfunc;//把信号处理函数赋给sa_sigaction
    act.sa_flags=SA_SIGINFO|SA_NODEFER;//SA_SIGINFO加上后，sa_sigaction信号处理函数生效
    int ret=sigaction(SIGINT,&act,NULL);//act是传入参数
    ERROR_CHECK(ret,-1,"sigaction");
    bzero(&act,sizeof(act));
     act.sa_sigaction=sigfunc;//把信号处理函数赋给sa_sigaction
    act.sa_flags=SA_SIGINFO|SA_NODEFER;//SA_SIGINFO加上后，sa_sigaction信号处理函数生效
    ret=sigaction(SIGQUIT,&act,NULL);//act是传入参数
    ERROR_CHECK(ret,-1,"sigaction");
    while(1);
    return 0;
}