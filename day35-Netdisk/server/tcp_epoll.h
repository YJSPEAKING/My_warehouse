#ifndef __TCP_EPOLL_H_
#define __TCP_EPOLL_H_
#include "head.h"
int tcp_init(int* socket_fd,char* ip,char* port);
int epoll_add(int epfd,int fd);
int epoll_del(int epfd,int fd);

#endif