#include <func.h>

int main(int argc,char** argv)
{
    ARGS_CHECK(argc,3);
    int sfd;
    sfd=socket(AF_INET,SOCK_STREAM,0);//初始化一个网络描述符，对应了一个缓冲区
    ERROR_CHECK(sfd,-1,"socket");
    printf("sfd=%d\n",sfd);
    struct sockaddr_in ser_addr;
    bzero(&ser_addr,sizeof(ser_addr));//清空
    ser_addr.sin_family=AF_INET;//代表要进行ipv4通信
    ser_addr.sin_addr.s_addr=inet_addr(argv[1]);//把ip的点分十进制转为网络字节序
    ser_addr.sin_port=htons(atoi(argv[2]));//把端口转为网络字节序
    //客户端就要去连接服务器
    int ret=connect(sfd,(struct sockaddr *)&ser_addr,sizeof(ser_addr));
    ERROR_CHECK(ret,-1,"connect");
    //编写即时聊天
    char buf[128]={0};
    fd_set rdset;
    while(1)
    {
        //清空集合并写入要监控的描述符
        FD_ZERO(&rdset);
        FD_SET(STDIN_FILENO,&rdset);
        FD_SET(sfd,&rdset);
        //监控哪一个描述符就绪
        ret=select(sfd+1,&rdset,NULL,NULL,NULL);
        if(FD_ISSET(STDIN_FILENO,&rdset))//如果标准输入可读
        {
            bzero(buf,sizeof(buf));
            ret=read(STDIN_FILENO,buf,sizeof(buf));
            if(!ret)
            {
                printf("I want go\n");
                break;
            }
            send(sfd,buf,strlen(buf)-1,0);//发送对应的字符串到对端，不带\n
        }
        if(FD_ISSET(sfd,&rdset))//如果sfd可读
        {
            bzero(buf,sizeof(buf));
            //服务器接收数据
            ret=recv(sfd,buf,sizeof(buf),0);
            ERROR_CHECK(ret,-1,"recv");
            if(!ret)//代表对方断开了
            {
                printf("byebye\n");
                break;
            }
            printf("%s\n",buf);
        }
    }
    close(sfd);
}