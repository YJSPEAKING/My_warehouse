#ifndef __OPER_H_
#define __OPER_H_
#include"head.h"
int register_n(char* new_name,char *salt, char *crypt_password);
int login(char* user_name,CInfo info);
int ls(int code,int user_id,char* buf);
int cd(char* oper,int* code,int user_id,char* path,char* name);
int rem(CInfo t,char* file_name,char* name);
int makd(CInfo t,char* dir_name);
int pd(CInfo t);
void salt(char* buf);
void token(char* user_name,char* buf);
int s_login(CInfo t,char* name);
int s_register(CInfo t,char* name);
int c_register(CInfo t);
int c_login(CInfo t);
int s_gets(pque_node t);
int c_gets(int fd,char* file);
int s_puts(pque_node t);
int c_puts(int fd,char* file);
// int specilal_gets(pque_node t,pfac d,int sfd);
int write_user(int rfd,int user_id,char* req);
#endif