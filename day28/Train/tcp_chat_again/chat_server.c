#include <func.h>
//聊天时，客户端断开了，能够再次支持客户端连上，继续聊
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
    //开始绑定
    int ret=bind(sfd,(struct sockaddr*)&ser_addr,sizeof(ser_addr));
    ERROR_CHECK(ret,-1,"bind");
    //开始监听,端口就开启了
    ret=listen(sfd,10);
    ERROR_CHECK(ret,-1,"listen");
    int new_fd;//new_fd才是和客户端进行交流的描述符
    struct sockaddr_in client_addr;
    bzero(&client_addr,sizeof(client_addr));
    socklen_t addr_len=sizeof(client_addr);
   
    //编写即时聊天
    char buf[128]={0};
    fd_set rdset,tmpset;//tmpset做传入传出参数
    FD_ZERO(&rdset);
    FD_SET(STDIN_FILENO,&rdset);
    FD_SET(sfd,&rdset);
    while(1)
    {
        //清空集合并写入要监控的描述符
        memcpy(&tmpset,&rdset,sizeof(fd_set));
        //监控哪一个描述符就绪
        ret=select(11,&tmpset,NULL,NULL,NULL);
        if(FD_ISSET(sfd,&tmpset))//如果sfd可读
        {
            //accept完成了3次握手,没有连接，accept会阻塞
            new_fd=accept(sfd,(struct sockaddr *)&client_addr,&addr_len);
            ERROR_CHECK(new_fd,-1,"accept");
            printf("client ip=%s,port=%d\n",inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));
            FD_SET(new_fd,&rdset);//有人连上了，添加到要监控的集合
        }
        if(FD_ISSET(STDIN_FILENO,&tmpset))//如果标准输入可读
        {
            bzero(buf,sizeof(buf));
            ret=read(STDIN_FILENO,buf,sizeof(buf));
            if(!ret)
            {
                printf("I want go\n");
                break;
            }
            send(new_fd,buf,strlen(buf)-1,0);//发送对应的字符串到对端，不带\n
        }
        if(FD_ISSET(new_fd,&tmpset))//如果new_fd可读
        {
            bzero(buf,sizeof(buf));
            //服务器接收数据
            ret=recv(new_fd,buf,sizeof(buf),0);
            ERROR_CHECK(ret,-1,"recv");
            if(!ret)//代表对方断开了
            {
                printf("byebye\n");
                FD_CLR(new_fd,&rdset);//从监控集合中移除
            }else{
                printf("%s\n",buf);
            }
        }
    }
    close(new_fd);//关闭对应的描述符
    close(sfd);
    return 0;
}