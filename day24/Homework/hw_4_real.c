//使用真实计时器，实用计时器，虚拟计时器，统计程序执行时间，在实用计时器及虚拟计时器设定计时后，先睡眠，再让程序处于while（1）
//真实计时器
#include<func.h>

void showtime(int signum)
{
    time_t curTime=time(NULL);
    printf("%s",ctime(&curTime));
}
int main()
{
    struct itimerval time;
    bzero(&time,sizeof(time));
    time.it_value.tv_sec=3;
    time.it_interval.tv_sec=2;
    signal(SIGALRM,showtime);
    showtime(-1);//手动调用一次看初次间隔
    int ret=setitimer(ITIMER_REAL,&time,NULL);
    while(1);
    return 0;
}