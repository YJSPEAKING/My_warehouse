//通过sigprocmask阻塞2号信号，睡眠5秒后，解除阻塞，2号信号得到执行；在睡眠后，解除阻塞之前，通过sigpending检测是否有信号挂起
#include<func.h>

int main()
{
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set,SIGINT);
    sigprocmask(SIG_BLOCK,&set,NULL);//屏蔽2号信号
    sleep(5);
    sigpending(&set);
    if(sigismember(&set,SIGINT))
    {
        printf("SIGINF is pending\n");
    }
    else{
        printf("no pending\n");
    }
    sigprocmask(SIG_UNBLOCK,&set,NULL);//解除二号信号屏蔽
    printf("you can't see me\n");
    return 0;
}