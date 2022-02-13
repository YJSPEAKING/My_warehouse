#include "func.h"

//循环接收data_len的sfd中数据到buf中
int recv_n(int sfd,void* buf,int data_len)
{
    char *p=(char*)buf;
    int total=0,ret;
    while(total<data_len)
    {
        ret=recv(sfd,p+total,data_len-total,0);
        if(0==ret)//对端断开
        {
            return -1;
        }
        //防止没有接收完就recv结束
        total+=ret;
    }
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
        total+=ret;
    }
    return 0;
}