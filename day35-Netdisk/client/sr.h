#ifndef __SR_H_
#define __SR_H_
#include"que.h"
#define GERS_PTHREAD 5//文件分成多少个传
typedef struct client_info{
    int fd;
    int code;
    char path[50];
    char token[50];
    int user_id;
}client_info,*CInfo;


typedef struct{
    int data_len;//存放buf，也就是火车车厢中数据长度
    char buf[4096];//火车车厢长度
}train_t;

typedef struct fac{
    Que que;  
    pthread_cond_t cond;
    pthread_t* pid;
    CInfo client;//直接以fd作为下标，省事
    int flag;
    int epfd;
}fac_t,*pfac;

typedef struct{
    OPER req;
}req_t;

int recv_n(int sfd,void* buf,long int data_size);
int send_n(int sfd,void* buf,long int data_size);
int send_str_n(int new_fd,char* buf);
int recv_str_n(int new_fd,char* buf);
int c_register(CInfo t);
int c_login(CInfo t,char* name);
int recv_file(int new_fd,char* file);
int send_file(int new_fd,char* file);
int c_puts(int fd,char* file);
int c_gets(int fd,char* file);
int req_send(int fd,req_t* t);
int req_recv(int fd,req_t* t);
int clogin(int fd,OPER req);
int map_send_file(int new_fd,char* file);
int map_recv_file(int new_fd,char* file);
int recv_map(int sfd,void* buf,long int data_size,long int start,int pfd);
int w_connect(int* sfd);
int fac_start(pfac t,int pthread_num);
int fac_init(pfac t,int pthread_num,int capacity);
void* child_gpfunc(void* p);
// void* gets_func(void* p);//舍弃的，放着参考
#endif