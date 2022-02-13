#include "process_pool.h"
//因为①client和server的文件传输速度不匹配，导致缓冲区满但send没结束时recv
//或因②客户端接收到的火车头的值正好为0
//则会导致客户端断开，造成server疯狂打印
//因此采用send_n和recv_n技术保证大文件的传输完整

//发送文件数据
int tran_file(int new_fd)
{
    int fd=open(FILENAME,O_RDONLY);//打开文件
    ERROR_CHECK(fd,-1,"open")
    train_t t;
    int ret;
    //发送文件名
    t.data_len=strlen(FILENAME);//火车头：文件名长度
    strcpy(t.buf,FILENAME);//火车车厢：文件名
    ret=send_n(new_fd,&t,4+t.data_len);//采用循环发送技术，发到new_fd中，客户端从new_fd中取即可
    SELFFUNC_ERR_CHECK(ret,"send_n")
    //发送文件大小内容
    struct stat buf;
    ret=stat(FILENAME,&buf);//通过stat获取文件大小
    ERROR_CHECK(ret,-1,"stat");
    t.data_len=sizeof(buf.st_size);
    memcpy(t.buf,&buf.st_size,sizeof(buf.st_size));
    ret=send_n(new_fd,&t,4+t.data_len);
    SELFFUNC_ERR_CHECK(ret,"send_n")
     //发送文件内容
    while(t.data_len=read(fd,t.buf,sizeof(t.buf)))
    {
        ret=send_n(new_fd,&t,4+t.data_len);
        SELFFUNC_ERR_CHECK(ret,"send_n");
    }
    t.data_len=0;
    ret=send_n(new_fd,&t,4+t.data_len);//文件内容发送完成标志
    SELFFUNC_ERR_CHECK(ret,"send_n");
    return 0;
}

//循环发送data_len的buf中数据到sfd中
int send_n(int sfd,void* buf,int data_len)
{
    char *p=(char*)buf;
    int total=0,ret;
    while(total<data_len)
    {
        ret=send(sfd,p+total,data_len-total,0);
        //考虑客户端主动断开的情况
        if(-1==ret)
        {
            return -1;
        }
        //防止没有全部发完就send结束
        total+=ret;
    }
    return 0;//别漏了这一步！
}

//循环接收data_len的sfd中数据到buf中
int recv_n(int sfd,void* buf,int data_len)
{
    char *p=(char*)buf;
    int total=0,ret;
    while(total<data_len)
    {
        ret=recv(sfd,p+total,data_len-total,0);
        //防止没有接收完就recv结束
        total+=ret;
    }
    return 0;
}