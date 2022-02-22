#include"sqloper.h"

int mySqlInit(MYSQL **conn,char *query)
{
    
    char* server="localhost";//需要在调用函数前准备好数据库三件套，query填入要执行的mysql语句，conn为传入传出 参数返回执行后的值
    char* user="root";//若使用了MYSQL_RES 需要记得free_result 和closs conn
    char* password="123";
    char* database="net";//要访问的数据库名称
    int t;
    *conn=mysql_init(NULL);
    if(!mysql_real_connect(*conn,server,user,password,database,0,NULL,0))
    {
        LOG1("Error connecting to database:");
        printf("%s\n",mysql_error(*conn));
        return -1;
    }
    t=mysql_query(*conn,query);
    if(t)
    {
        LOG1("Error making query:");
        printf("%s\n",mysql_error(*conn));
        mysql_close(*conn);
        return -1;
    }
    else
    {
        LOG1("sql connect");
        return 0;
    }
}
//插入新用户
int table_register_insert(char *salt,char* crypt_password,char* user_name,int code)
{
    MYSQL *conn;
    char query[300];
    sprintf(query,"insert into register values(0,'%s','%s','%s',%d);",salt,crypt_password,user_name,code);
    LOG1(query);//日志
    int ret = mySqlInit(&conn,query);
    if(-1==ret)
    {
        LOG1("mySql register inserrt error");
        mysql_close(conn);
        return -1;
    }
    else {
        LOG1("mySql register inserrt success");
        return 0;
    }
}
//sel_cond要先拼接，因为selcct会用and，会将所有表信息通过传入传出参数返回
int table_register_select(char* sel_cond,int* user_id,char *salt,char* crypt_password,char* user_name,int *code)
{
	MYSQL *conn;//连接
	MYSQL_RES *res;//结果操作指针
	MYSQL_ROW row;//一行的数据是存在row中间
    char query[300];
    sprintf(query,"select * from register where %s;",sel_cond) ;
    LOG1(query);
	int ret = mySqlInit(&conn,query);
    res=mysql_use_result(conn);//获取结果
    if(res)
    {
        if((row=mysql_fetch_row(res))!=NULL)
        {	
            if(user_id!=NULL){*user_id=atoi(row[0]);}
            if(salt!=NULL) {memcpy(salt,row[1],strlen(row[1]));}
            if(crypt_password!=NULL){memcpy(crypt_password,row[2],strlen(row[2]));}
            if(user_name!=NULL){memcpy(user_name,row[3],strlen(row[3]));}
            if(code!=NULL){*code=atoi(row[4]);}
        }
        else{
            LOG1("register select don't find data");
            mysql_free_result(res);
            mysql_close(conn);
            return -1;
        }
    }
    mysql_free_result(res);
    mysql_close(conn);
    return 0;
}

//改注册表
int table_register_update(int user_id,char *salt,char* crypt_password,char* user_name,int code)
{
    MYSQL *conn;
    char query[300];
    sprintf(query,"update register set salt='%s',crypt_password='%s',user_name='%s',code=%d where user_id=%d;",\
    salt,crypt_password,user_name,code,user_id);
    LOG1(query);//日志
    int ret = mySqlInit(&conn,query);
    if(-1==ret)
    {
        LOG1("mySql register update error");
        mysql_close(conn);
        return -1;
    }
    else {
        LOG1("mySql register update success");
        return 0;
    }
}
//依靠对应user_id注销user（file，register，code都要删）
int table_register_delete(int user_id)
{
    MYSQL *conn;
    char query[300];
    sprintf(query,"delete from register where user_id=%d;",user_id);
    LOG1(query);//日志
    int ret = mySqlInit(&conn,query);
    if(-1==ret)
    {
        LOG1("mySql register del error");
        mysql_close(conn);
        return -1;
    }
    else {
        LOG1("mySql register del success");
        return 0;
    }
}

//插入新code
int table_code_insert(int user_id,int code)
{
    MYSQL *conn;
    char query[300];
    sprintf(query,"insert into r_code values(%d,%d);",user_id,code);
    LOG1(query);//日志
    int ret = mySqlInit(&conn,query);
    if(-1==ret)
    {
        LOG1("mySql code inserrt error");
        mysql_close(conn);
        return -1;
    }
    else {
        LOG1("mySql code inserrt success");
        return 0;
    }
}
//sel_cond要先拼接，因为selcct会用and，会将所有表信息通过传入传出参数返回
int table_code_select(char* sel_cond,int* user_id,int* code)
{
	MYSQL *conn;//连接
	MYSQL_RES *res;//结果操作指针
	MYSQL_ROW row;//一行的数据是存在row中间
    char query[300];
    sprintf(query,"select * from r_code where %s;",sel_cond) ;
    LOG1(query);
	int ret = mySqlInit(&conn,query);
    res=mysql_use_result(conn);//获取结果
    if(res)
    {
        if((row=mysql_fetch_row(res))!=NULL)
        {	
            if(user_id!=NULL){*user_id=atoi(row[0]);}
            if(code!=NULL){*code=atoi(row[1]);}
        }
        else{
            LOG1("code select don't find data");
            mysql_free_result(res);
            mysql_close(conn);
            return -1;
        }
    }
    mysql_free_result(res);
    mysql_close(conn);
    return 0;
}
//依靠对应user_id注销user（file，register，code都要删）
int table_code_delete(int user_id)
{
    MYSQL *conn;
    char query[300];
    sprintf(query,"delete from r_code where user_id=%d;",user_id);
    LOG1(query);//日志
    int ret = mySqlInit(&conn,query);
    if(-1==ret)
    {
        LOG1("mySql code delete error");
        mysql_close(conn);
        return -1;
    }
    else {
        LOG1("mySql code delete success");
        return 0;
    }
}

int table_file_insert(int precode,char* file_type,char* file_name,int user_id,int file_size,char* md5)
{
    MYSQL *conn;
    char query[300];
    sprintf(query,"insert into file values(0,%d,'%s','%s',%d,%d,'%s');",precode,file_type,file_name,user_id,file_size,md5);
    LOG1(query);//日志
    int ret = mySqlInit(&conn,query);
    if(-1==ret)
    {
        LOG1("mySql file inserrt error");
        mysql_close(conn);
        return -1;
    }
    else {
        LOG1("mySql file inserrt success");
        return 0;
    }
}
//sel_cond要先拼接，因为selcct会用and，会将所有表信息通过传入传出参数返回
int table_file_select(char* sel_cond,int* code,int* precode,char* file_type,char* file_name,int* user_id,int* file_size,char* md5)
{
	MYSQL *conn;//连接
	MYSQL_RES *res;//结果操作指针
	MYSQL_ROW row;//一行的数据是存在row中间
    char query[300];
    sprintf(query,"select * from file where %s;",sel_cond) ;
    LOG1(query);
	int ret = mySqlInit(&conn,query);
    res=mysql_use_result(conn);//获取结果
    if(res)
    {
        if((row=mysql_fetch_row(res))!=NULL)
        {	
            if(code!=NULL){*code=atoi(row[0]);}
            if(precode!=NULL){*precode=atoi(row[1]);}
            if(file_type!=NULL){memcpy(file_type,row[2],strlen(row[2]));}
            if(file_name!=NULL){memcpy(file_name,row[3],strlen(row[3]));}
            if(user_id!=NULL){*user_id=atoi(row[4]);}
            if(file_size!=NULL){*file_size=atoi(row[5]);}
            if(md5!=NULL){memcpy(md5,row[6],strlen(row[6]));}
        }
        else{
            LOG1("file select don't find data");
            mysql_free_result(res);
            mysql_close(conn);
            return -1;
        }
    }
    mysql_free_result(res);
    mysql_close(conn);
    return 0;
}
//改file表
int table_file_update(int code,int precode,char* file_type,char* file_name,int user_id,int file_size,char* md5)
{
    MYSQL *conn;
    char query[300];
    sprintf(query,"update file set precode=%d,file_type='%s',file_name='%s',user_id=%d,file_size=%d,md5='%s' where code=%d;",\
    precode,file_type,file_name,user_id,file_size,md5,code);
    LOG1(query);//日志
    int ret = mySqlInit(&conn,query);
    if(-1==ret)
    {
        LOG1("mySql file update error");
        mysql_close(conn);
        return -1;
    }
    else {
        LOG1("mySql file update success");
        return 0;
    }
}
//依靠对应user_id注销user（file，register，code都要删）
int table_file_delete(int code)
{
    MYSQL *conn;
    char query[300];
    sprintf(query,"delete from file where code=%d;",code);
    LOG1(query);//日志
    int ret = mySqlInit(&conn,query);
    if(-1==ret)
    {
        LOG1("mySql file del error");
        mysql_close(conn);
        return -1;
    }
    else {
        LOG1("mySql file del success");
        return 0;
    }
}
