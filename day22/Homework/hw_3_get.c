//创建消息队列，发送消息，接收消息，删除消息队列
#include<func.h>

struct msgbuf{
    long mtype;
    char mtext[128];
};
int main(int argc, char* argv[])//发送端
{
    ARGS_CHECK(argc,3)
    int msqid=msgget(1000,IPC_CREAT|0600);
    ERROR_CHECK(msqid,-1,"msgget")
    struct msgbuf msg;
    bzero(&msg,sizeof(msg));
    msg.mtype=atoi(argv[1]);
    strcpy(msg.mtext,argv[2]);
    int ret=msgsnd(msqid,&msg,strlen(msg.mtext),0);//扔到消息队列去
    ERROR_CHECK(ret,-1,"msgsnd");
    return 0;
}
#include<func.h>

struct msgbuf{
    long mtype;
    char mtext[128];
};
int main(int argc,char* argv[])//接收端
{
    ARGS_CHECK(argc,2)
    int msqid=msgget(1000,IPC_CREAT|0600);
    ERROR_CHECK(msqid,-1,"msgget")
    struct msgbuf msg;
    bzero(&msg,sizeof(msg));
    int ret=msgrcv(msqid,&msg,sizeof(msg.mtext),atoi(argv[1]),0);//倒数第二个参数控制接收的消息类型
    ERROR_CHECK(ret,-1,"msgrcv");
    printf("message recieved:%s\n",msg.mtext);
    return 0;
}