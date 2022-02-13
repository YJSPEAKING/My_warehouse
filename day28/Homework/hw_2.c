//通过select实现客户端断开后，能够再次连接的设计
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
    
    char buf[128]={0};
    fd_set set,tmpset;
    FD_ZERO(&set);
    FD_SET(STDIN_FILENO,&set);
    FD_SET(sfd,&set);
    while(1)//实现服务器端不会被动终止
    {
        memcpy(&tmpset,&set,sizeof(set));//把set复制给小弟
        ret=select(11,&tmpset,NULL,NULL,NULL);//maxfd自定，最大1024
        if(FD_ISSET(sfd,&tmpset))//sfd可读，说明sfd缓冲区来活了，该accept了
        {
            new_fd=accept(sfd,(struct sockaddr*)&client_addr,&addr_len);//注意返回给new_fd
            ERROR_CHECK(new_fd,-1,"accept")
            printf("connect established.INFO=%s:%d\n",inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));
            FD_SET(new_fd,&set);
        }
        ERROR_CHECK(ret,-1,"select")
        if(FD_ISSET(STDIN_FILENO,&tmpset))
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
        if(FD_ISSET(new_fd,&tmpset))
        {
            bzero(buf,sizeof(buf));
            ret=recv(new_fd,buf,sizeof(buf),0);
            ERROR_CHECK(ret,-1,"recv")
            if(!ret)
            {
                printf("系统提示:对方已断开连接。\n");
                FD_CLR(new_fd,&set);//不break了，改为把newfd移除
            }
            else{
                printf("客户端:%s\n",buf);      
            }   
        }
    }
    close(sfd);
    close(new_fd);
    return 0;
}