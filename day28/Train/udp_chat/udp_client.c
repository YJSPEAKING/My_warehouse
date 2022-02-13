#include <func.h>

//udp即时聊天
int main(int argc,char** argv)
{
    ARGS_CHECK(argc,3);
    int sfd=socket(AF_INET,SOCK_DGRAM,0);
    ERROR_CHECK(sfd,-1,"socket");
    struct sockaddr_in ser_addr;
    bzero(&ser_addr,sizeof(ser_addr));//清空
    ser_addr.sin_family=AF_INET;//代表要进行ipv4通信
    ser_addr.sin_addr.s_addr=inet_addr(argv[1]);//把ip的点分十进制转为网络字节序
    ser_addr.sin_port=htons(atoi(argv[2]));//把端口转为网络字节序
    sendto(sfd,"hello",5,0,(struct sockaddr*)&ser_addr,sizeof(ser_addr));
    char buf[128]={0};
    fd_set rdset;
    int ret;
    while(1)
    {
        //清空集合并写入要监控的描述符
        FD_ZERO(&rdset);
        FD_SET(STDIN_FILENO,&rdset);
        FD_SET(sfd,&rdset);
        //监控哪一个描述符就绪
        ret=select(sfd+1,&rdset,NULL,NULL,NULL);
        if(FD_ISSET(STDIN_FILENO,&rdset))
        {
            //读取标准输入，并发给对方
            bzero(buf,sizeof(buf));
            read(STDIN_FILENO,buf,sizeof(buf));
            sendto(sfd,buf,strlen(buf)-1,0,(struct sockaddr*)&ser_addr,sizeof(ser_addr));
        }
        if(FD_ISSET(sfd,&rdset))
        {
            //sfd可读，对方发了数据，读取
            bzero(buf,sizeof(buf));
            ret=recvfrom(sfd,buf,sizeof(buf),0,NULL,NULL);
            printf("%s\n",buf);
        }
    }
    close(sfd);
    return 0;
}