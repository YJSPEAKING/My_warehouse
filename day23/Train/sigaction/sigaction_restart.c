#include <func.h>

void sigfunc(int signum,siginfo_t *p,void *p1)
{
    printf("sig %d is coming\n",signum);
}

//sigaction 基本使用，捕捉2号信号
//使用了SA_RESTART标志后,卡在系统调用时，信号来了，系统调用不会出错
int main()
{
    struct sigaction act;
    //一定要注意清空
    bzero(&act,sizeof(act));
    act.sa_sigaction=sigfunc;//把信号处理函数赋给sa_sigaction
    act.sa_flags=SA_SIGINFO|SA_RESTART;//SA_SIGINFO加上后，sa_sigaction信号处理函数生效
    int ret=sigaction(SIGINT,&act,NULL);
    ERROR_CHECK(ret,-1,"sigaction");
    char buf[100]={0};
    ret=read(STDIN_FILENO,buf,sizeof(buf));//read读取输入
    printf("ret=%d,buf=%s",ret,buf);
    return 0;
}