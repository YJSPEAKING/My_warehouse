#include "func.h"

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
    //接收文件名
    int data_len;
    char buf[1000]={0};
    recv(sfd,&data_len,4,0);//接文件名长度
    recv(sfd,buf,data_len,0);//接文件名
    int fd=open(buf,O_WRONLY|O_CREAT,0666);
    ERROR_CHECK(fd,-1,"open");
    //接收文件内容
    while(1)
    {
        recv(sfd,&data_len,4,0);//接文件内容长度
        if(data_len>0)
        {
            recv(sfd,buf,data_len,0);//接文件内容
            write(fd,buf,data_len);//把文件内容写到文件里
        }else{
            break;
        }
    }
    close(fd);
    close(sfd);
}