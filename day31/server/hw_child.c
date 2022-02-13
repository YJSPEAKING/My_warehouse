#include "process_pool.h"

//创建多个子进程
int make_child(process_data_t *p_manage,int process_num)
{
    int i;
    pid_t pid;
    int fds[2];//socketpair会创造一个全双工的管道
    int ret;
    for(i=0;i<process_num;i++)
    {
        ret=socketpair(AF_LOCAL,SOCK_STREAM,0,fds);
        ERROR_CHECK(ret,-1,"socketpair");
        //子进程用fds[0]与父进程的fds[1]交流，fds[0]与fds[1]均既可读也可写
        pid=fork();
        if(pid==0)//子进程
        {
            close(fds[1]);
            child_handle(fds[0]);
        }else{//父进程
            close(fds[0]);
            p_manage[i].pid=pid;
            p_manage[i].fd=fds[1];
            p_manage[i].busy=0;//默认子进程是非忙碌状态
#ifdef DEBUG
        printf("p_manage[%d].fd=%d\n",i,p_manage[i].fd);
#endif
        }
    }
}

//子进程的代码流程
int child_handle(int fd)
{
    int new_fd,ret;//子进程要接收一个new_fd,通过new_fd给对应的客户端发文件
    char flag=1;
    while(1)
    {
        recv_fd(fd,&new_fd);//接收任务
        printf("gets task,new_fd=%d\n",new_fd);
        tran_file(new_fd);//发文件给客户端
        close(new_fd);
        write(fd,&flag,sizeof(flag));//通知父进程完成任务
    }
}