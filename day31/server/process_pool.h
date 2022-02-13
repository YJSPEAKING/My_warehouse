#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <time.h>
#include <grp.h>
#include <pwd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/select.h>
#include <sys/time.h>
#include <strings.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/msg.h>
#include <signal.h>
#include <pthread.h>
#include <errno.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/epoll.h>
#define ARGS_CHECK(argc,num) {if(argc!=num) {printf("error args\n");return -1;}}
#define ERROR_CHECK(ret,retval,func_name) {if(ret==retval) {printf("errno=%d,",errno);fflush(stdout);perror(func_name);return -1;}}
#define THREAD_ERR_CHECK(ret,func_name) {if(ret!=0) {printf("%s failed,%d %s\n",func_name,ret,strerror(ret));return -1;}}
#define SELFFUNC_ERR_CHECK(ret,func_name) {if(ret!=0) {printf("%s failed\n",func_name);return -1;}}

#define FILENAME "file"

typedef struct{
    pid_t pid;//每个子进程的pid
    int fd;//子进程的对端
    short busy;//子进程是否忙碌，如果是0代表非忙碌，1代码忙碌
}process_data_t;

//不要交换data_len和buf的定义顺序
typedef struct{
    int data_len;//存放buf，也就是火车车厢中数据长度
    char buf[1000];//火车车厢长度
}train_t;

//创建多个子进程
int make_child(process_data_t* p_manage,int process_num);
//子进程的代码流程
int child_handle(int fd);
//socket,bind,listen的初始化过程
int tcp_init(int* socket_fd,char* ip,char* port);
//对fd进行注册，监控它是否可读
int epoll_add(int epfd,int fd);
//接收描述符
int recv_fd(int sfd,int *fd);
//做一种仪式，让内核控制信息发生进程间的dup机制
int send_fd(int sfd,int fd);
//发送文件给客户端
int tran_file(int new_fd);
//循环接收数据，直到接收到自己想要数量
int recv_n(int sfd,void* buf,int data_len);
//循环发送数据，直到发送到自己想要数量
int send_n(int sfd,void* buf,int data_len);