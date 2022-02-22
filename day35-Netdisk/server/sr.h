#ifndef __SR_H_
#define __SR_H_
#include"head.h"
#include"factory.h"
#define FILENAME "基于深度学习的食用水果图像识别应用研究_付安安.caj" 
//不要交换data_len和buf的定义顺序
typedef struct{
    int data_len;//存放buf，也就是火车车厢中数据长度
    char buf[4096];//火车车厢长度
}train_t;

typedef struct{
    int data_len;//存放buf，也就是火车车厢中数据长度
    OPER req;
    char buf[4096];//火车车厢长度
}train_nt;

typedef struct{
    OPER req;
}req_t;

int send_n(int sfd,void* buf,long int data_size);
int recv_n(int sfd,void* buf,long int data_size);
int tran_file(int new_fd,char* file);
int tran_file_n(int new_fd,OPER req,char* file);
int send_str_n(int new_fd,char* buf);
int recv_str_n(int new_fd,char* buf);
int recv_file(int new_fd,char* file);
int send_file(int new_fd,char* file);
int req_send(int fd,req_t* t);
int req_recv(int fd,req_t* t);
int map_send_file(int new_fd,char* file);
int map_recv_file(int new_fd,char* file);
int recv_map(int sfd,void* buf,long int data_size,long int start,int pfd);
// int map_gets_send(int new_fd,char* file,pfac t,int sfd);
#endif