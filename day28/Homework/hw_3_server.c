//通过udp实现即时聊天
#include<func.h>

int main(int argc,char* argv[])
{
    ARGS_CHECK(argc,3)
    //socket套接字
    int sfd=socket(AF_INET,SOCK_DGRAM,0);
    ERROR_CHECK(sfd,-1,"socket")
    struct sockaddr_in server_addr;
    bzero(&server_addr,sizeof(server_addr));
    server_addr.sin_addr.s_addr=inet_addr(argv[1]);
    server_addr.sin_port=htons(atoi(argv[2]));
    server_addr.sin_family=AF_INET;
    //bind
    int ret=bind(sfd,(struct sockaddr*)&server_addr,sizeof(server_addr));
    ERROR_CHECK(ret,-1,"bind");
    struct sockaddr_in client_addr;
    bzero(&client_addr,sizeof(client_addr));
    socklen_t addr_len=sizeof(client_addr);
    char buf[128]={0};
    ret=recvfrom(sfd,buf,sizeof(buf),0,(struct sockaddr*)&client_addr,&addr_len);//听一次，知道对方是谁了
    ERROR_CHECK(ret,-1,"recvfrom")
    printf("INFO=%s:%d\n",inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));
    fd_set set;
    while(1)//没搞new_fd,监控sfd即可
    {
        FD_ZERO(&set);
        FD_SET(STDIN_FILENO,&set);
        FD_SET(sfd,&set);
        ret=select(sfd+1,&set,NULL,NULL,NULL);
        ERROR_CHECK(ret,-1,"select")
        if(FD_ISSET(STDIN_FILENO,&set))
        {
            bzero(buf,sizeof(buf));
            ret=read(STDIN_FILENO,buf,sizeof(buf));
            ERROR_CHECK(ret,-1,"read")
            ret=sendto(sfd,buf,strlen(buf)-1,0,(struct sockaddr*)&client_addr,sizeof(client_addr));
            ERROR_CHECK(ret,-1,"sendto")
        }
        if(FD_ISSET(sfd,&set))
        {
            bzero(buf,sizeof(buf));
            ret=recvfrom(sfd,buf,sizeof(buf),0,NULL,NULL);//无连接，无四次挥手，双方都不知道对方有没有断开
            ERROR_CHECK(ret,-1,"recvfrom")
            printf("客户端:%s\n",buf);
        }
    }
    close(sfd);
    return 0;
}