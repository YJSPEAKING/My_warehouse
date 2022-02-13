//完成进程池，某个客户端连接后能够下载文件，进程池这边打印显示分配任务给子进程，然后子进程完成任务
#include "process_pool.h"

int main(int argc,char**argv)
{
    if(argc!=4)
    {
        printf("./process_poll_server IP PORT PROCESS_NUM\n");
        return -1;
    }
    int process_num=atoi(argv[3]);
    //用p_manage管理子进程信息
    process_data_t *p_manage=(process_data_t *)calloc(process_num,sizeof(process_data_t));
    make_child(p_manage,process_num);

    int socket_fd;
    tcp_init(&socket_fd,argv[1],argv[2]);

    //初始化epoll，父进程既要监控socket_fd，也要监控每一个子进程的管道对端
    int epfd=epoll_create(1);
    int ret=epoll_add(epfd,socket_fd);
    SELFFUNC_ERR_CHECK(ret,"epoll_add");
    int i;
    for(i=0;i<process_num;i++)
    {
        ret=epoll_add(epfd,p_manage[i].fd);
        SELFFUNC_ERR_CHECK(ret,"epoll_add");
    }
    int new_fd,j;
    int ready_fd_num;//就绪的描述符数量
    struct epoll_event *evs=(struct epoll_event *)calloc(process_num+1,sizeof(struct epoll_event));
    struct sockaddr_in client_addr;
    char flag;
    while(1)
    {
        ready_fd_num=epoll_wait(epfd,evs,process_num+1,-1);
        for(i=0;i<ready_fd_num;i++)
        {
            //父进程等待是否有客户端连接，一旦有客户端连接，accept接收，得到new_fd
            //new_fd传递给非忙碌的子进程，把它标记为忙碌
            if(evs[i].data.fd==socket_fd)
            {
                bzero(&client_addr,sizeof(client_addr));
                socklen_t addr_len=sizeof(client_addr);
                new_fd=accept(socket_fd,(struct sockaddr*)&client_addr,&addr_len);
                printf("%s %d is connect\n",inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));
                for(j=0;j<process_num;j++)//找到非忙碌的子进程
                {
                    if(0==p_manage[j].busy)
                    {
                        send_fd(p_manage[j].fd,new_fd);//发任务给子进程
                        p_manage[j].busy=1;//对应的子进程被标记为忙碌
                        printf("child %d is busy\n",p_manage[j].pid);
                        break;
                    }
                }
                close(new_fd);//无论是否找到空闲子进程，都关闭new_fd
            }
            //如果收到子进程的通知，把对应子进程标记为非忙碌
            for(j=0;j<process_num;j++)
            {
                if(evs[i].data.fd==p_manage[j].fd)//说明对应的子进程发通知了
                {
                    read(p_manage[j].fd,&flag,sizeof(flag));//把数据读出来
                    p_manage[j].busy=0;
                    printf("child %d is not busy\n",p_manage[j].pid);
                    break;
                }
            }
        }
    }
    return 0;
}