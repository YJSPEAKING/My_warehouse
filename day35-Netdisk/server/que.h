#ifndef __QUE_H_
#define __QUE_H_ 
#include"head.h"
#define GERS_PTHREAD 5//文件分成多少个传
typedef enum{
    CD,
    LS,
    REMOVE,
    PWD,
    MKDIR,
    REGISTER,
    LOGIN,
    GETS,
    PUTS,
    TOKEN,
    EXIT
}OPER;

typedef struct que_node{
    int fd;
    int code;
    int user_id;
    OPER req;
    char file_name[200];
    struct que_node* next;
}que_node,*pque_node;

typedef struct{
    pque_node head,tail;
    int size;
    int capacity;
    pthread_mutex_t mutex;
}Que,*pQue;

typedef struct gets_node{
    long start;
    long end;
    int fd;//放sfd
    char* p;
    struct gets_node* next;
}gets_node,*pgets_node;

// typedef struct{
//     pgets_node head,tail;
//     int size;
//     int capacity;
//     pthread_mutex_t mutex;
// }Qgets,*pQgets;

//初始化队列
int que_init(pQue t,int capacity);
//插入队列
int que_insert(pQue t,int fd);
int que_insert_n(pQue t,pque_node d);
//取出队列元素
int que_get(pQue t,int* fd);
int que_get_n(pQue t,pque_node d);
// int qgets_init(pQgets t,int capacity);
// int qgets_insert_n(pQgets t,pgets_node d);
// int qgets_get_n(pQgets t,pgets_node d);
#endif
