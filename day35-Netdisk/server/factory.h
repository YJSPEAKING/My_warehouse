#ifndef __FACTORY_H_
#define __FACTORY_H_
#include"head.h"
#include"que.h"
typedef struct client_info{
    int flag;//0无效，1有效
    int login;//0没有登录，1已经登录
    int fd;
    int code;
    char path[50];
    char token[50];
    int user_id;
    int circle;//轮盘法，%30，
}client_info,*CInfo;

typedef struct fac{
    Que que;
    pthread_cond_t cond;
    pthread_t* pid;
    CInfo client;//直接以fd作为下标，省事
    int flag;
    int epfd;
}fac_t,*pfac;

//工厂初始化
int fac_init(pfac t,int pthread_num,int capacity);
//开工
int fac_start(pfac t,int pthread_num);
//子线程函数
void* child_func(void* p);
//net子线程，做gets,puts
void* child_gpfunc(void* p);
int wlogin(CInfo t);
int token_check(int fd,char* token);
//gets 特供版子线程函数
// void* gets_func(void* p);
#endif