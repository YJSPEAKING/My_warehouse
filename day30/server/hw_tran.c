#include "process_pool.h"

//发送文件数据
int tran_file(int new_fd)
{
    train_t t;
    //发送文件名
    t.data_len=strlen(FILENAME);//火车头：文件名长度
    strcpy(t.buf,FILENAME);//火车车厢：文件名
    send(new_fd,&t,4+t.data_len,0);//发到new_fd中，客户端从new_fd中取即可
    //发送文件内容
    int fd=open(FILENAME,O_RDONLY);//打开文件
    ERROR_CHECK(fd,-1,"open")
    //每次读t.buf大小的内容，一个车厢一个车厢地运，直到文件fd所指缓冲区中没东西
    while(t.data_len=read(fd,t.buf,sizeof(t.buf)))//火车车厢：FILENAME中的内容
    {
        send(new_fd,&t,4+t.data_len,0);
    }
    //发送文件结束标志
    t.data_len=0;
    send(new_fd,&t,4+t.data_len,0);
    close(new_fd);
}