//通过select实现tcp的即时聊天
#include<func.h>

int main(int argc,char* argv[])
{
    ARGS_CHECK(argc,3)
    //socket套接字
    socklen_t sfd=socket(AF_INET,SOCK_STREAM,0);
    ERROR_CHECK(sfd,-1,"socket")
    struct sockaddr_in server_addr;
    bzero(&server_addr,sizeof(server_addr));
    server_addr.sin_addr.s_addr=inet_addr(argv[1]);
    server_addr.sin_port=htons(atoi(argv[2]));
    server_addr.sin_family=AF_INET;
    //connect
    int ret=connect(sfd,(struct sockaddr*)&server_addr,sizeof(server_addr));
    ERROR_CHECK(ret,-1,"connect")
    char buf[128]={0};
    fd_set set;
    while(1)
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
            if(!ret)
            {
                printf("系统提示:您已主动终止对话。\n");
                break;
            }
            ret=send(sfd,buf,strlen(buf)-1,0);
            ERROR_CHECK(ret,-1,"send")
        }
        if(FD_ISSET(sfd,&set))
        {
            bzero(buf,sizeof(buf));
            ret=recv(sfd,buf,sizeof(buf),0);
            ERROR_CHECK(ret,-1,"recv")
            if(!ret)
            {
                printf("系统提示:对方已断开连接。\n");
                break;
            }
            printf("服务器:%s\n",buf);
        }
    }
    close(sfd);
    return 0;
}