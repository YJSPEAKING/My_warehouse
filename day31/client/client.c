#include "func.h"

int main(int argc,char** argv)
{
    ARGS_CHECK(argc,3);
    //第一步：进行TCP连接
    int sfd;
    sfd=socket(AF_INET,SOCK_STREAM,0);//初始化一个网络描述符，对应了一个缓冲区
    ERROR_CHECK(sfd,-1,"socket");
    printf("sfd=%d\n",sfd);
    struct sockaddr_in ser_addr;
    bzero(&ser_addr,sizeof(ser_addr));//清空
    ser_addr.sin_family=AF_INET;//代表要进行ipv4通信
    ser_addr.sin_addr.s_addr=inet_addr(argv[1]);//把ip的点分十进制转为网络字节序
    ser_addr.sin_port=htons(atoi(argv[2]));//把端口转为网络字节序
    //客户端连接服务器
    int ret=connect(sfd,(struct sockaddr *)&ser_addr,sizeof(ser_addr));
    ERROR_CHECK(ret,-1,"connect");

    //第二步：得到时间
    struct timeval start,end;
    gettimeofday(&start,NULL);//得到当前时间

    //第三步：接收文件名、文件大小和文件内容
    //接收文件名
    int data_len;
    char buf[1000]={0};
    ret=recv_n(sfd,&data_len,4);//接文件名长度
    SELFFUNC_ERR_CHECK(ret,"recv_n")
    ret=recv_n(sfd,buf,data_len);//接文件名
    SELFFUNC_ERR_CHECK(ret,"recv_n")
    int fd=open(buf,O_WRONLY|O_CREAT,0666);
    ERROR_CHECK(fd,-1,"open");

    //接收文件大小
    ret=recv_n(sfd,&data_len,4);
    SELFFUNC_ERR_CHECK(ret,"recv_n")
    off_t file_size;//文件大小
    ret=recv_n(sfd,&file_size,data_len);
    SELFFUNC_ERR_CHECK(ret,"recv_n")

    //接收文件内容并打印进度
    char *p=(char*)buf;
    off_t slice_size=file_size/10000;//文件大小的万分之一
    off_t total=0,last_size=0;//total是当前大小，last_size上一次大小
    while(1)
    {
        ret=recv_n(sfd,&data_len,4);//接文件内容长度
        SELFFUNC_ERR_CHECK(ret,"recv_n")
        if(data_len>0)
        {
            ret=recv_n(sfd,buf,data_len);//接文件内容
            SELFFUNC_ERR_CHECK(ret,"recv_n")
            write(fd,buf,data_len);//把文件内容写到文件里
            total+=data_len;
            if(total-last_size>slice_size)//打印进度
            {
                printf("%6.2lf%%\r",(double)total/file_size*100);
                fflush(stdout);
                last_size=total;
            }
        }else{
            printf("100.00%%\n");
            break;
        }    
    }
    gettimeofday(&end,NULL);
    printf("use time=%ld\n",(end.tv_sec-start.tv_sec)*1000000+end.tv_usec-start.tv_usec);
    close(fd);
    close(sfd);
    return 0;
}