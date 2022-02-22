#include"que.h"
#include"sqloper.h"
#include"factory.h"
#include"oper.h"
#include"sr.h"
#include"md5.h"
//---------------------------------------------------------------------

//此文件中的函数都是知晓什么命令之后发生的事，这里设计成先发命令后发用户名等信息


//------------------------------------------------------------------------
//返回-1：注册表有了，不需要重复注册,这个函数仅仅是对数据库的操作,
int register_n(char* new_name,char *salt, char *crypt_password)
{
    char buf[200];
    bzero(buf,sizeof(buf));
    int user_id,code;
    sprintf(buf,"user_name='%s'",new_name);
    int ret=table_register_select(buf,NULL,NULL,NULL,NULL,NULL);
    if(ret!=-1){
        LOG1("table register have this title");
        return -1;//注册表有了，不需要重复注册
    }
    table_register_insert(salt,crypt_password,new_name,-1);//插入注册表，此时不知道code，先用-1代替
    table_register_select(buf,&user_id,NULL,NULL,NULL,NULL);//拿user_id
    char md5[MD5_STR_LEN + 1]={0};
    Compute_file_md5("file",md5);
    table_file_insert(0,"d",new_name,user_id,0,md5);//用户根目录插入文件表，目录不记录file_size
    bzero(buf,sizeof(buf));
    sprintf(buf,"user_id=%d",user_id);
    table_file_select(buf,&code,NULL,NULL,NULL,NULL,NULL,NULL);//拿code
    table_register_update(user_id,salt,crypt_password,new_name,code);
    return 0;
}
//fd在函数外填，注册时没有对t填入信息
int s_register(CInfo t,char* name)
{
    char user_name[20]={0},buf[200]={0};
    int ret=recv_str_n(t->fd,user_name);//收用户名
    LOG1(user_name);
    strcpy(name,user_name);
    ERROR_CHECK(ret,-1,"recv_n");
    LOG1(user_name);
    sprintf(buf,"user_name='%s'",user_name);
    //注册表有没有
    ret=table_register_select(buf,NULL,NULL,NULL,NULL,NULL);
    if(-1==ret){
        send_str_n(t->fd,"y");
    }else if(0==ret){
        send_str_n(t->fd,"n");
        return -1;
    }
    //发盐值
    char bufs[50]={0};
    char bufc[50]={0};
    salt(bufs);
    ret=send_str_n(t->fd,bufs);//发盐值
    ERROR_CHECK(ret,-1,"send salt");
    ret=recv_str_n(t->fd,bufc);//收加密的密码
    ERROR_CHECK(ret,-1,"recv spasswrd");
    ret=register_n(user_name,bufs,bufc);
    ERROR_CHECK(ret,-1,"register_n");//数据库操作
    return 0;
}

int c_register(CInfo t)
{
    char user_name[20]={0},passwrd[50]={0},salt[50]={0},buf[200]={0};
    scanf("%s%s",user_name,passwrd);
    int ret=send_str_n(t->fd,user_name);//发用户名
    ERROR_CHECK(ret,-1,"send user_name error");
    recv_str_n(t->fd,buf);
    if(0==strcmp(buf,"n")){
        LOG1("已经注册该用户");
        return -1;
    }
    ret=recv_str_n(t->fd,salt);//收盐值
    ERROR_CHECK(ret,-1,"receive salt error");
    char *spasswrd;
    spasswrd=crypt(passwrd,salt);//加密
    ret=send_str_n(t->fd,spasswrd);//发密码
    ERROR_CHECK(ret,-1,"send spasswrd error");
    return 0;
}
//填入fd就可以了
int s_login(CInfo t,char* name)
{
    char c_passwrd[50]={0},buf[200]={0},cp[50]={0};
    char user_name[20]={0};
    char salt[50]={0};
    int ret;
    recv_str_n(t->fd,user_name);//收用户名
    strcpy(name,user_name);
    recv_str_n(t->fd,c_passwrd);//收密码
    LOG1(user_name);
    LOG1(c_passwrd);
    sprintf(buf,"user_name='%s'",user_name);
    ret=table_register_select(buf,&t->user_id,salt,cp,NULL,&t->code);//拿各种值
    if(-1==ret){
        LOG1("without this user, please register");
        send_str_n(t->fd,"no");
        return -1;
    }
    char* p=crypt(c_passwrd,salt);
    LOG1("s_md5:");
    LOG1(p);
    LOG1("c_md5:");
    LOG1(cp);
    if(0==strcmp(p,cp)){
        ret=send_str_n(t->fd,"log");//密码正确，登陆成功
        LOG1("LOG success");
        ERROR_CHECK(ret,-1,"send_str_n");
    }else{
        send_str_n(t->fd,"fail");//密码错误，登录失败
        LOG1("LOG fail");
        ERROR_CHECK(ret,-1,"send_str_n");
        return -1;
    }
    //发TOKEN
    bzero(t->token,sizeof(t->token));
    token(user_name,t->token);
    LOG1("token has generated");
    LOG1(t->token);
    ret=send_str_n(t->fd,t->token);
    ERROR_CHECK(ret,-1,"token send error");
    LOG1("token has been send");
    bzero(buf,sizeof(buf));
    recv_str_n(t->fd,buf);
    LOG1(buf);
    if(0==strcmp(buf,"tok")){
        ret=login(user_name,t);
        LOG1("tok");
        ERROR_CHECK(ret,-1,"log in error:database operate error");
        return 0;
    }else{
        return -1;
    }   
}

int c_login(CInfo t)
{
    char user_name[20]={0},passwrd[50]={0},buf[200]={0};
    scanf("%s%s",user_name,passwrd);
    int ret=send_str_n(t->fd,user_name);//发用户名
    ERROR_CHECK(ret,-1,"send user");
    send_str_n(t->fd,passwrd);//发密码
    ERROR_CHECK(ret,-1,"send passwrd");
    recv_str_n(t->fd,buf);
    ERROR_CHECK(ret,-1,"recv flag");//收是否正确
    if(0==strcmp(buf,"log")){
        recv_str_n(t->fd,t->token);  
    }else if(0==strcmp(buf,"fail")){
        printf("密码错误\n");
        return -1;
    }else{
        printf("没有注册\n");
        return -1;
    }
    LOG1("等token");
    recv_str_n(t->fd,t->token);
    LOG1(t->token);
    send_str_n(t->fd,"tok");
    return 0;
}

//CInfo是队列中client的信息，以INFO[*]的形式传入（这里以fd为下标）,这个函数仅仅是对数据库是操作,将code,user_id,path填入
int login(char* user_name,CInfo info)
{
    char buf[200];
    bzero(buf,sizeof(buf));
    int code,user_id;
    sprintf(buf,"user_name='%s'",user_name);
    int ret=table_register_select(buf,&user_id,NULL,NULL,NULL,&code);
    if(ret==-1){
        LOG1("table register haven't this title");
        return -1;//注册表莫得，要注册
    }
    info->code=code;
    info->user_id=user_id;
    bzero(info->path,sizeof(info->path));
    memcpy(info->path,"/",sizeof("/"));
    LOG1("LOG1 IN success");
    return 0;
}

//找多个,结果放buf
int ls(int code,int user_id,char* buf)
{
	MYSQL *conn;//连接
	MYSQL_RES *res;//结果操作指针
	MYSQL_ROW row;//一行的数据是存在row中间
    char query[300];
    sprintf(query,"select * from file where precode=%d and user_id=%d;",code,user_id) ;
    LOG1(query);
	int ret = mySqlInit(&conn,query);
    res=mysql_use_result(conn);//获取结果
    if(res)
    {
        while((row=mysql_fetch_row(res))!=NULL)
        {	
            strcat(buf,row[3]);
            strcat(buf," ");
        }
    }
    mysql_free_result(res);
    mysql_close(conn);
    return 0;
}
//oper是看三种里的哪种情况
int cd(char* oper,int* code,int user_id,char* path,char* name)
{
    char file_name[50]={0};
    int precode,ret;
    char buf[128]={0};  
    sprintf(buf,"code=%d",*code);
    ret=table_file_select(buf,NULL,&precode,NULL,file_name,NULL,NULL,NULL);
    ERROR_CHECK(ret,-1,"table_file_select");
    if(0==strcmp(oper,".."))
    {
        LOG3("CD:","..");
        *code=precode;//code=precode
        path[strlen(path)-strlen(file_name)-1]='\0';
    }else if(0==strcmp(oper,"/")){
        LOG3("CD:","/");
        bzero(buf,sizeof(buf));
        sprintf(buf,"user_id=%d",user_id);
        ret=table_register_select(buf,NULL,NULL,NULL,name,code);//code=注册表记录的根目录
        ERROR_CHECK(ret,-1,"table_register_select");
        memcpy(path,"/",sizeof("/"));
    }else{
        LOG3("CD:",file_name);
        char type[5]={0};
        bzero(buf,sizeof(buf));
        sprintf(buf,"precode=%d and user_id=%d and file_name='%s'",*code,user_id,oper);
        ret=table_file_select(buf,code,NULL,type,NULL,NULL,NULL,NULL);
        ERROR_CHECK(ret,-1,"table_file_select");
        LOG1("TYPE:");
        LOG1(type);
        if(0==strcmp(type,"d")){
            strcat(path,oper);
            strcat(path,"/");
        }else if(0==strcmp(type,"f")){
            LOG1("cd error,use type d instead type f");
            return -1;
        }
    }
    LOG1("PATH:");
    LOG1(path);
    return 0;
}

int rem(CInfo t,char* file_name,char* name)
{
    int code,ret;
    char md5[50]={0};
    char buf[350]={0};
    sprintf(buf,"precode=%d and user_id=%d and file_name='%s'",t->code,t->user_id,file_name);
    ret=table_file_select(buf,&code,NULL,NULL,NULL,NULL,NULL,md5);
    ERROR_CHECK(ret,-1,"table_file_select");
    unlink(md5);//md5作为文件名
    LOG3("remove，",file_name);
    ret=table_file_delete(code);
    ERROR_CHECK(ret,-1,"table_file_delete");
    bzero(buf,sizeof(buf));
    sprintf(buf,"user_id=%d'",t->user_id);
    ret=table_register_select(buf,NULL,NULL,NULL,name,NULL);
    return 0;
}

int makd(CInfo t,char* dir_name)
{
    int ret=table_file_insert(t->code,"d",dir_name,t->user_id,0,0);
    ERROR_CHECK(ret,-1,"table_file_insert");
    return 0;
}

int pd(CInfo t)
{
    printf("%s\n",t->path);
    return 0;
}
//盐值生成，buf要先初始化为0,16字节盐值
void salt(char* buf)
{
    srand(time(NULL));
    for(int i=0;i<16;i++){
        buf[i]=rand()%26+'A';
    }
}
void token(char* user_name,char* buf)
{
    salt(buf);
    strcat(buf,user_name);
}
//数据库找这个名字的文件，md5才是名字
int s_gets(pque_node t)
{
    char buf[300]={0};
    char md5[50]={0};
    char file[200]={0};
    memcpy(file,t->file_name,strlen(t->file_name));
    LOG1(file);
    sprintf(buf,"user_id=%d and precode=%d and file_name='%s'",t->user_id,t->code,file);
    int ret=table_file_select(buf,NULL,NULL,NULL,NULL,NULL,NULL,md5);
    if(-1==ret){
        LOG1("gets:文件没找到");
        ret=send_str_n(t->fd,"n");
        ERROR_CHECK(ret,-1,"gets:flag error");
        return -1;
    }else{
        LOG1("gets:flag发送");
        LOG2("里面的fd=",t->fd);
        ret=send_str_n(t->fd,"y");
        ERROR_CHECK(ret,-1,"gets:flag error");
        LOG1("gets:flag发送完成");
    }
    LOG1("gets:文件准备发送");
    LOG1(md5);
    ret=map_send_file(t->fd,md5);//发过去什么名字跟实际什么名字没关系，名字靠recv生成，客户端ls能看见
    ERROR_CHECK(ret,-1,"gets:文件传输出错");
    LOG1("gets:文件传输进入队列");
    return 0;
}
//此函数使用在已经发送命令时
int c_gets(int fd,char* file)
{
    char buf[200]={0};
    recv_str_n(fd,buf);
    LOG1("收到flag");
    if(0==strcmp(buf,"n")){
        printf("没有此文件");
        return -1;
    }else if(0==strcmp(buf,"y")){
        LOG1("正在接收文件");
        map_recv_file(fd,file);
    }
    return 0;
}

//收文件，用md5命名,这里file是文件名
int s_puts(pque_node t)
{
    char file[200]={0};
    memcpy(file,t->file_name,strlen(t->file_name));
    LOG3("子线程取出的节点:",t->file_name);
    LOG3("memcpy后",file);
    char c_md5[50]={0},s_md5[50]={0},buf[128]={0};//客户端的md5，服务器端的md5
    recv_str_n(t->fd,c_md5);//先收MD5
    LOG1("md5 received");
    sprintf(buf,"md5='%s' and user_id=%d and precode=%d",c_md5,t->user_id,t->code);//查当前目录当前用户有没有
    int ret=table_file_select(buf,NULL,NULL,NULL,NULL,NULL,NULL,NULL);
    if(0==ret){//查到了当前目录有
        ret=send_str_n(t->fd,"n");
        ERROR_CHECK(ret,-1,"当前目录有，send错误");
        return 0;
    }else{//没查到
        ret=send_str_n(t->fd,"y");
        ERROR_CHECK(ret,-1,"当前目录没有该文件，但send错误");
    }
    bzero(buf,sizeof(buf));
    sprintf(buf,"md5='%s'",c_md5);
    ret=table_file_select(buf,NULL,NULL,NULL,NULL,NULL,NULL,NULL);
    if(0==ret){//查到别人或别的目录有
        ret=send_str_n(t->fd,"n");
        ERROR_CHECK(ret,-1,"puts在发送服务器有该文件");
        memcpy(s_md5,c_md5,strlen(c_md5));
    }else{//都没有，传文件
        ret=send_str_n(t->fd,"y");
        ERROR_CHECK(ret,-1,"puts在传送没有该文件");
        ret=map_recv_file(t->fd,c_md5);//以客户端md5命名
        LOG1("sending file");
        ERROR_CHECK(ret,-1,"recd_file");
        Compute_file_md5(c_md5,s_md5);//以客户发来的md5命名，计算这个文件的MD5，两者比较
    }
    if(0==strcmp(c_md5,s_md5)){
        struct stat status;
        stat(c_md5,&status);
        table_file_insert(t->code,"f",file,t->user_id,status.st_size,s_md5);
        LOG1("puts数据库操作完毕");
        printf("fd:%d\n",t->fd);
        send_str_n(t->fd,"y");//文件正确
        LOG1("发送flag完毕");
        return 0;
    }else{
        send_str_n(t->fd,"n");//文件有错误
        unlink(c_md5);
        return -1;
    }
}

int c_puts(int fd,char* file)
{
    char md5[50]={0};
    char buf[200]={0};
    Compute_file_md5(file,md5);
    int ret=send_str_n(fd,md5);//发md5
    ERROR_CHECK(ret,-1,"send_str_n");
    LOG1("md5 has been send");
    ret=recv_str_n(fd,buf);
    ERROR_CHECK(ret,-1,"第一个falg错误")
    if(0==strcmp(buf,"y")){
        bzero(buf,sizeof(buf));
        ret=recv_str_n(fd,buf);
        ERROR_CHECK(ret,-1,"第二个flag错误");
        if(0==strcmp(buf,"y")){
            LOG1("传输文件");
        }else{
            LOG1("快传");
            return 0;
        }
        bzero(buf,sizeof(buf));
    }else{
        printf("该目录有此文件\n");
        return 0;
    }
    ret=map_send_file(fd,file);//发file
    ERROR_CHECK(ret,-1,"map_send_file");
    LOG1("文件已经发送");
    ret=recv_str_n(fd,buf);
    ERROR_CHECK(ret,-1,"recv_str_n");
    LOG1("flag已经接收:");
    LOG1(buf);
    if(0==strcmp(buf,"y")){//收flag
        printf("puts success\n");
        return 0;
    }else{
        printf("puts false\n");
        return -1;
    }
}

// int specilal_gets(pque_node t,pfac d,int sfd)
// {
//     char buf[300]={0};
//     char md5[50]={0};
//     char file[200]={0};
//     memcpy(file,t->file_name,strlen(t->file_name));
//     LOG1(file);
//     sprintf(buf,"user_id=%d and precode=%d and file_name='%s'",t->user_id,t->code,file);
//     int ret=table_file_select(buf,NULL,NULL,NULL,NULL,NULL,NULL,md5);
//     if(-1==ret){
//         LOG1("gets:文件没找到");
//         ret=send_str_n(t->fd,"n");
//         ERROR_CHECK(ret,-1,"gets:flag error");
//         return -1;
//     }else{
//         LOG1("gets:flag发送");
//         ret=send_str_n(t->fd,"y");
//         ERROR_CHECK(ret,-1,"gets:flag error");
//         LOG1("gets:flag发送完成");
//     }
//     LOG1("gets:文件准备发送");
//     LOG1(md5);
//     ret=map_gets_send(t->fd,md5,d,sfd);//分开发送
//     ERROR_CHECK(ret,-1,"gets:文件传输出错");
//     LOG1("gets:文件传输进入队列");
//     return 0;
// }
//日志函数
int write_user(int rfd,int user_id,char* req)
{
    char name[200]={0};
    time_t now;
    char buf[500]={0};
    sprintf(buf,"user_id=%d",user_id);
    table_register_select(buf,NULL,NULL,NULL,name,NULL);
    time(&now);
    bzero(buf,sizeof(buf));
    sprintf(buf,"客户%s于%s%s\n",name,ctime(&now),req);
    write(rfd,buf,sizeof(buf));
    return 0;
}