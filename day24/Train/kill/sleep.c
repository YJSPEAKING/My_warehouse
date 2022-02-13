#include <func.h>

void sigfunc(int signum)
{
    //除了唤醒什么都不做
}

int main()
{
    signal(SIGALRM,sigfunc);//设置ALRM信号的信号处理行为
    alarm(3);//3秒后会向当前进程发送alarm信号
    pause();//去睡眠队列
    return 0;
}