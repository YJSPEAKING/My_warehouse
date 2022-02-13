#include <func.h>

//udp的客户端
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
    recvfrom(sfd,buf,sizeof(buf),0,NULL,NULL);
    printf("%s\n",buf);
    close(sfd);
    return 0;
}