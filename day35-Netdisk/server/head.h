#ifndef __HEAD_H__
#define __HEAD_H__
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
#include <sys/sendfile.h>
#include <mysql/mysql.h>
#include <sys/types.h>      
#define ARGS_CHECK(argc,num) {if(argc!=num) {printf("error args\n");return -1;}}
#define ERROR_CHECK(ret,retval,func_name) {if(ret==retval) {printf("errno=%d,",errno);LOG1(func_name);fflush(stdout);perror(func_name);return -1;}}
#define THREAD_ERR_CHECK(ret,func_name) {if(ret!=0) {printf("%s failed,%d %s\n",func_name,ret,strerror(ret));return -1;}}
#define SELFFUNC_ERR_CHECK(ret,func_name) {if(ret!=0) {printf("%s failed\n",func_name);return -1;}}
#define LOG1(info) printf("%s:%d---%s\n",__FILE__,__LINE__,info); 
#define LOG2(info1,info2) printf("%s:%d---%s%d\n",__FILE__,__LINE__,info1,info2); 
#define LOG2l(info1,info2) printf("%s:%d---%s%ld\n",__FILE__,__LINE__,info1,info2); 
#define LOG3(info1,info2) printf("%s:%d---%s%s\n",__FILE__,__LINE__,info1,info2); 
#define RETURN_INFO(ret,fd,r_str,f_str) {if(ret==-1) {LOG1(f_str);send_str_n(fd,f_str);continue;}else{LOG1(r_str);send_str_n(fd,r_str);}}


#endif