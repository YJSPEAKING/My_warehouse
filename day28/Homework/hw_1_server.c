//通过select实现tcp的即时聊天
#include<func.h>

int main(int argc,char* argv[])
{
    ARGS_CHECK(argc,3)
    //socket套接字
    int sfd=socket(AF_INET,SOCK_STREAM,0);
    ERROR_CHECK(sfd,-1,"socket")
    struct sockaddr_in server_addr;
    bzero(&server_addr,sizeof(server_addr));
    server_addr.sin_addr.s_addr=inet_addr(argv[1]);
    server_addr.sin_port=htons(atoi(argv[2]));
    server_addr.sin_family=AF_INET;
    //bind
    int ret=bind(sfd,(struct sockaddr*)&server_addr,sizeof(server_addr));
    ERROR_CHECK(ret,-1,"bind");
    //listen
    ret=listen(sfd,10);
    ERROR_CHECK(ret,-1,"listen")
    //accept
    int new_fd;
    struct sockaddr_in client_addr;
    bzero(&client_addr,sizeof(client_addr));
    socklen_t addr_len=sizeof(client_addr);
    new_fd=accept(sfd,(struct sockaddr*)&client_addr,&addr_len);//注意返回给new_fd
    ERROR_CHECK(new_fd,-1,"accept")
    printf("connect established.INFO=%s:%d\n",inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));
    char buf[128]={0};
    fd_set set;
    while(1)
    {
        FD_ZERO(&set);
        FD_SET(STDIN_FILENO,&set);
        FD_SET(new_fd,&set);
        ret=select(new_fd+1,&set,NULL,NULL,NULL);
        ERROR_CHECK(ret,-1,"select")
        if(FD_ISSET(STDIN_FILENO,&set))
        {
            bzero(buf,sizeof(buf));
            ret=read(STDIN_FILENO,buf,sizeof(buf));
            if(!ret)
            {
                printf("系统提示:您已主动终止对话。\n");
                break;
            }
            ret=send(new_fd,buf,strlen(buf)-1,0);
            ERROR_CHECK(ret,-1,"send")
        }
        if(FD_ISSET(new_fd,&set))
        {
            bzero(buf,sizeof(buf));
            ret=recv(new_fd,buf,sizeof(buf),0);
            ERROR_CHECK(ret,-1,"recv")
            if(!ret)
            {
                printf("系统提示:对方已断开连接。\n");
                break;
            }
            printf("客户端:%s\n",buf);
        }
    }
    close(sfd);
    close(new_fd);
    return 0;
}