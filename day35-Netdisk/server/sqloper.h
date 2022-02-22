#ifndef __SQLOPER_H_
#define __SQLOPER_H_
#include"head.h"
int mySqlInit(MYSQL **conn,char *query);
int table_register_insert(char *salt,char* crypt_password,char* user_name,int code);
int table_register_select(char* sel_cond,int* user_id,char *salt,char* crypt_password,char* user_name,int *code);
int table_register_update(int user_id,char *salt,char* crypt_password,char* user_name,int code);
int table_register_delete(int user_id);
int table_code_insert(int user_id,int code);
int table_code_select(char* sel_cond,int* user_id,int* code);
int table_code_delete(int user_id);
int table_file_insert(int precode,char* file_type,char* file_name,int user_id,int file_size,char* md5);
int table_file_select(char* sel_cond,int* code,int* precode,char* file_type,char* file_name,int* user_id,int* file_size,char* md5);
int table_file_update(int code,int precode,char* file_type,char* file_name,int user_id,int file_size,char* md5);
int table_file_delete(int code);
#endif