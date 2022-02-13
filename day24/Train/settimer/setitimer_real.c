#include <func.h>

void sigfunc(int signum)
{
    time_t now=time(NULL);
    printf("当前时间是%s",ctime(&now));
}
//真实计时器
int main()
{
    signal(SIGALRM,sigfunc);
    struct itimerval t;
    bzero(&t,sizeof(t));
    t.it_value.tv_sec=3;//初始间隔设置为3秒
    t.it_interval.tv_sec=2;//重复间隔设置为2秒
    int ret;
    sigfunc(0);//在timer启动之前先显示一下当前时间
    ret=setitimer(ITIMER_REAL,&t,NULL);
    ERROR_CHECK(ret,-1,"setitimer");
    char buf[128]={0};
    read(STDIN_FILENO,buf,sizeof(buf));
    printf("buf=%s\n",buf);
    return 0;
}