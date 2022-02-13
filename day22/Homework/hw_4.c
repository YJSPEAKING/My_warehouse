#include<func.h>

void func(int signum)
{
    printf("signal %d has been intercepted\n",signum);
    sleep(10);
    printf("signal %d's func is over\n",signum);
}

int main()
{
    signal(SIGINT,func);
    signal(SIGQUIT,func);
    while(1);
    return 0;
}