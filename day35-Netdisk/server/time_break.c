#include"head.h"
#include"time_break.h"
//与上一次相比过了一秒没有
int one_second(long last)
{
    long now=time(NULL);
    if(now-last>=60){
        return 1;
    }else{
        return 0;
    }
}
//weather connect,-1有连接，0是断开
int w_connect(int sfd)
{
    int ret;
    char t;
    ret=recv(sfd,&t,0,MSG_DONTWAIT);//-1有连接，0是断开
    LOG2("ret=%3d\r",ret);
    fflush(stdout);
    return ret;
}