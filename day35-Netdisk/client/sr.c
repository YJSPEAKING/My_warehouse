#include<func.h>
#include"que.h"
#include"sr.h"
#include"head.h"
#include"md5.h"

#include"sr.h"
int c_register(CInfo t)
{
    char user_name[20]={0},passwrd[50]={0},salt[50]={0},buf[50]={0};
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

int c_login(CInfo t,char* name)
{
    char user_name[20]={0},passwrd[50]={0},buf[50]={0};
    scanf("%s%s",user_name,passwrd);
    int ret=send_str_n(t->fd,user_name);//发用户名
    ERROR_CHECK(ret,-1,"send user");
    send_str_n(t->fd,passwrd);//发密码
    ERROR_CHECK(ret,-1,"send passwrd");
    recv_str_n(t->fd,buf);
    ERROR_CHECK(ret,-1,"recv flag");//收是否正确
    if(0==strcmp(buf,"log")){
        LOG1("等token");
        bzero(t->token,sizeof(t->token));
        recv_str_n(t->fd,t->token);
        LOG1(t->token);
        send_str_n(t->fd,"tok");  
        memcpy(name,user_name,strlen(user_name));
        return 0;
    }else if(0==strcmp(buf,"fail")){
        printf("密码错误\n");
        return -1;
    }else{
        printf("没有注册\n");
        return -1;
    }
}

int recv_n(int sfd,void* buf,long int data_size)
{
    long int total=0,ret=0;
    char *p=(char*)buf;
    while(total<data_size)
    {
        ret=recv(sfd,p+total,data_size-total,0);
        if(-1==ret)
        {
            break;
        }
        total+=ret;
    }
    return 0;
}

int send_n(int sfd,void* buf,long int data_size)
{
    long int total=0,ret=0;
    char *p=(char*)buf;
    while(total<data_size)
    {
        ret=send(sfd,p+total,data_size-total,0);
        if(-1==ret)
        {
            printf("client break");
            return -1;
        }
        total+=ret;
    }
    return 0;
}

int send_str_n(int new_fd,char* buf)
{
    int len=strlen(buf),ret;
    ret=send_n(new_fd,&len,4);
    ERROR_CHECK(ret,-1,"send_n");
    ret=send_n(new_fd,buf,len);
    ERROR_CHECK(ret,-1,"send_n");
    return 0;
}

int recv_str_n(int new_fd,char* buf)
{
    int len,ret;
    ret=recv_n(new_fd,&len,4);
    LOG2("LEN=",len);
    ERROR_CHECK(ret,-1,"recv_n");
    ret=recv_n(new_fd,buf,len);
    LOG1("recv str");
    ERROR_CHECK(ret,-1,"recv_n");
    return 0;
}

//不传文件名
int send_file(int new_fd,char* file)
{
    train_t t;
    struct stat status;
    LOG1(file);
    int fd=open(file,O_RDONLY);
    ERROR_CHECK(fd,-1,"open file");
    stat(file,&status);
    t.data_len=status.st_size;
    int ret=send_n(new_fd,&t,4);
    ERROR_CHECK(ret,-1,"send_n");
    LOG1("长度发送完毕");
    printf("len=%d\n",t.data_len);
    while(t.data_len=read(fd,t.buf,sizeof((t.buf))))
    {
        ret=send_n(new_fd,&t,4+t.data_len);
        ERROR_CHECK(ret,-1,"send_n");
    }
    t.data_len=0;
    send_n(new_fd,&t,4+t.data_len);
    ERROR_CHECK(ret,-1,"send_n");
    LOG1("结束符发送完毕");
    return 0;
}
//收文件，没有文件名
int recv_file(int new_fd,char* file)
{
    int len,ret,total=0;
    ret=recv_n(new_fd,&len,4);
    ERROR_CHECK(ret,-1,"recv_n");
    LOG1("已经收到长度");
    if(0==len){
        LOG1("传输长度=0，错误(是否文件不存在)");
        return -1;
    }
    int fd=open(file,O_RDWR|O_CREAT,0666);
    ftruncate(fd,len);
    char* p=mmap(NULL,len,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
    while(1){
        ret=recv_n(new_fd,&len,4);
        ERROR_CHECK(ret,-1,"recv_file");
        if(0==len){
            LOG1("收到结束符");
            break;
        }
        ret=recv_n(new_fd,p+total,len);
        if(-1==ret){
            return -1;
        }
        total+=len;
    }
    return 0;
}

int c_puts(int fd,char* file)
{
    char md5[50]={0};
    char buf[50]={0};
    Compute_file_md5(file,md5);
    LOG1("正在发送md5");
    int ret=send_str_n(fd,md5);//发md5
    LOG1("md5发送完毕");
    ERROR_CHECK(ret,-1,"send_str_n");
    LOG1(md5);
    ret=recv_str_n(fd,buf);
    ERROR_CHECK(ret,-1,"第一个falg错误")
    if(0==strcmp(buf,"y")){
        bzero(buf,sizeof(buf));
        ret=recv_str_n(fd,buf);
        ERROR_CHECK(ret,-1,"第二个flag错误");
        if(0==strcmp(buf,"y")){
            LOG1("传输文件");
        }else if(0==strcmp(buf,"n")){
            LOG1("快传");
            bzero(buf,sizeof(buf));
            recv_str_n(fd,buf);
            if(0==strcmp(buf,"y")){
                LOG1("快传完成");
            }else if(0==strcmp(buf,"n")){
                LOG1("快传失败（数据库操作）");
            }else{
                LOG1("奇异错误");
            }
            return 0;
        }  
    }else if(0==strcmp(buf,"n")){
        printf("该目录有此文件\n");
        return 0;
    }
    ret=map_send_file(fd,file);//发file
    ERROR_CHECK(ret,-1,"map_send_file");
    bzero(buf,sizeof(buf));
    LOG1("文件已经发送");
    ret=recv_str_n(fd,buf);
    ERROR_CHECK(ret,-1,"recv_str_n");
    LOG1("flag已经接收:");
    LOG1(buf);
    if(0==strcmp(buf,"y")){//收flag
        printf("c_puts success\n");
        return 0;
    }else{
        printf("c_puts false\n");
        return -1;
    }
}

int c_gets(int fd,char* file)
{
    char buf[100]={0};
    LOG1("收flag");
    int len;
    bzero(buf,sizeof(buf));
    recv_str_n(fd,buf);
    LOG1("收到flag");
    if(0==strcmp(buf,"n")){
        printf("没有此文件");
        return -1;
    }else if(0==strcmp(buf,"y")){
        LOG1("正在接收文件");
        map_recv_file(fd,file);
    }
    else{
        LOG1("奇异错误");
        LOG1(buf);
        return -1;
    }
    return 0;
}
int req_send(int fd,req_t* t)
{
    return send_n(fd,t,sizeof(req_t));
}

int req_recv(int fd,req_t* t)
{
    return recv_n(fd,t,sizeof(req_t));
}
//除了登陆注册连服务器的第一件事
int clogin(int fd,OPER req)
{
    req_t t;
    char buf[50];
    t.req=req;
    LOG1("check ING");
    req_send(fd,&t);
    bzero(buf,sizeof(buf));
    recv_str_n(fd,buf);
    if(0==strcmp(buf,"n")){
        printf("没有登录\n");
        return -1;
    }     
    LOG1("登录完成");
    return 0;
}

int map_send_file(int new_fd,char* file)
{
    long int start=0,ret;
    ret=recv_n(new_fd,&start,8);//收起始点
    
    ERROR_CHECK(ret,-1,".part");
    struct stat status;
    LOG3("opening:",file);
    int fd=open(file,O_RDWR,0666);
    ERROR_CHECK(fd,-1,"map send open");
    stat(file,&status);
    long int len=status.st_size;   
    LOG2l("map sending len:",len);
    ret=send_n(new_fd,&len,8);//发送文件大小，fturncat直接建立
    LOG1("map send len finish:");
    ERROR_CHECK(ret,-1,"len");
    char* p=mmap(NULL,len,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
    LOG1("map file sendinng");
    LOG2l("start=",start);
    ret=send_n(new_fd,p+start,len-start);//发文件
    LOG1("map file send finish");
    ERROR_CHECK(ret,-1,"map file send");
    ret=munmap(p,len);
    ERROR_CHECK(ret,-1,"munmap");
    return 0;
}
int map_recv_file(int new_fd,char* file)
{
    //先看看有没有.part
    char buf[350]={0},part_name[350]={0};
    long int start=0;
    sprintf(part_name,"%s.part",file);
    int pfd=open(part_name,O_RDWR,0666);
    if(-1==pfd){//没有，偏移0
        pfd=open(part_name,O_RDWR|O_CREAT,0666);//没有就创建
        start=0;
    }else{//有，记录偏移
        bzero(buf,sizeof(buf));
        read(pfd,&start,4);
    }
    send_n(new_fd,&start,8);//发送偏移
    LOG2l("start=",start);
    //接文件大小
    long int len=0;
    LOG1("map recv len:");
    recv_n(new_fd,&len,8);
    LOG2l("map recv len:",len);
    LOG3("opening:",file);
    int fd=open(file,O_RDWR|O_CREAT,0666);
    ERROR_CHECK(fd,-1,"map recv open fail");
    ftruncate(fd,len);
    char* p=mmap(NULL,len,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
    //直接收
    // LOG2("pfd=",pfd);
    LOG1("map file recv");
    int ret=recv_map(new_fd,p,len,start,pfd);
    LOG1("map flie recv finish");
    ERROR_CHECK(ret,-1,"recv file fail");
    ret=munmap(p,len);
    ERROR_CHECK(ret,-1,"munmap");
    unlink(part_name);
    printf("recv finish");
    close(pfd);
    return 0;
}
//断点续传专用，start是发了多少，pfd是.part
int recv_map(int sfd,void* buf,long int data_size,long int start,int pfd)
{
    long int total=start,ret=0,last;
    last=total;
    char *p=(char*)buf;
    LOG1("recv_map接收中");
    long int change=data_size/100;
    printf("开始传输，total=%ld,data_size=%ld\n",total,data_size);
    while(total<data_size)
    {
        
        ret=recv(sfd,p+total,data_size-total,0);
        if(-1==ret)
        {
            break;
        }
        
        start+=ret;
        lseek(pfd,0,SEEK_SET);
        write(pfd,&start,4);
        total+=ret;
        if(change<total-last){
            last=total;
            printf("进度:%6.2lf%%\r",(double)total/data_size*100);
            fflush(stdout);
        }
    }
    if(total==data_size){
        printf("进度:100.00%%\n");
    }
    LOG1("recv_map接收完毕");
    return 0;
}
//由于这里由scanf会卡住，所以不担心多次close
int w_connect(int* sfd)
{
    int ret;
    char t;
    ret=recv(*sfd,&t,0,MSG_DONTWAIT);//-1有连接，0是断开
    LOG2("ret=%3d\r",ret);
    if(0==ret){
        close(*sfd);
        *sfd=socket(AF_INET,SOCK_STREAM,0);
    }
    return ret;
}

int fac_init(pfac t,int pthread_num,int capacity)
{
    que_init(&t->que,capacity);
    pthread_cond_init(&t->cond,NULL);
    t->pid=(pthread_t*)calloc(pthread_num,sizeof(pthread_t));
    t->client=(CInfo)calloc(t->que.capacity+10,sizeof(client_info));
    t->flag=0;
}

int fac_start(pfac t,int pthread_num)
{
    pthread_t pid;
    if(0==t->flag)
    {
        for(int i=0;i<pthread_num;i++){
            pthread_create(t->pid+i,NULL,child_gpfunc,t);
            LOG2("子线程:",i);
        }
        return 0;
    }
    else
        return -1;
}

// void* gets_func(void* p)
// {
//     int ret;
//     long start,len;
//     pfac t=(pfac)p;
//     gets_node node;
//     while(1)
//     {
//         LOG1("锁");
//         pthread_mutex_lock(&t->gque.mutex);
//         if(0==t->que.size) {
//            pthread_cond_wait(&t->gcond,&t->gque.mutex);
//            LOG1("解锁");
//         }
//         qgets_get_n(&t->gque,&node);
//         pthread_mutex_unlock(&t->gque.mutex);
//         int fd=socket(AF_INET,SOCK_STREAM,0);
//         ret=connect(fd,(struct sockaddr *)&t->gque.addr,sizeof(t->gque.addr));
//         recv_n(fd,&start,8);
//         recv_n(fd,&len,8);
//         recv_n(fd,node.p+start,len);
//         munmap(p+start,len);
//         close(fd);
//         pthread_mutex_lock(&t->temp.mutex);
//         t->temp.size++;
//         if(GERS_PTHREAD==t->temp.size){
//             t->temp.size=0;
//             close(node.fd);
//         }
//         pthread_mutex_unlock(&t->temp.mutex);
//     }
// }

void* child_gpfunc(void* p)
{
    int ret;
    char buf[200]={0};
    pfac t=(pfac)p;
    que_node qnode;
    while(1)
    {
        LOG1("锁");
        pthread_mutex_lock(&t->que.mutex);
        if(0==t->que.size) {
           pthread_cond_wait(&t->cond,&t->que.mutex);
           LOG1("解锁");
        }
        que_get_n(&t->que,&qnode);
        pthread_mutex_unlock(&t->que.mutex);
        int fd=socket(AF_INET,SOCK_STREAM,0);
        LOG2("port:",ntohs(qnode.addr.sin_port));
        ret=connect(fd,(struct sockaddr *)&qnode.addr,sizeof(qnode.addr));
        LOG2("连接成功,fd=",fd);
        if(GETS==qnode.req){
            LOG1("子线程启动下载");
            LOG3("子线程file name:",qnode.file_name);
            ret=c_gets(fd,qnode.file_name);
            bzero(buf,sizeof(buf));
            recv_str_n(fd,buf);      
            if(0==strcmp(buf,"y")){
                printf("gets success\n");
            }
            else{
                printf("gets error\n");
            }
        }
        else if(PUTS==qnode.req){
            LOG1("子线程启动上传");
            LOG3("子线程file name:",qnode.file_name);
            c_puts(fd,qnode.file_name);
            bzero(buf,sizeof(buf));
            recv_str_n(fd,buf);
            if(0==strcmp(buf,"y")){
                printf("puts success\n");
            }
            else{
                printf("puts error\n");
                continue;
            }
       }  
       close(fd);//统一关闭
    }

}

//gets专用
int map_gets_send(int new_fd,char* file)
{
    long int start=0,ret;
    ret=recv_n(new_fd,&start,8);//收起始点
    
    ERROR_CHECK(ret,-1,".part");
    struct stat status;
    LOG3("opening:",file);
    int fd=open(file,O_RDWR,0666);
    ERROR_CHECK(fd,-1,"map send open");
    stat(file,&status);
    long int len=status.st_size;   
    LOG2l("map sending len:",len);
    ret=send_n(new_fd,&len,8);//发送文件大小，fturncat直接建立
    LOG1("map send len finish:");
    ERROR_CHECK(ret,-1,"len");
    char* p=mmap(NULL,len,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
    LOG1("map file sendinng");
    LOG2l("start=",start);
    ret=send_n(new_fd,p+start,len-start);//发文件
    LOG1("map file send finish");
    ERROR_CHECK(ret,-1,"map file send");
    ret=munmap(p,len);
    ERROR_CHECK(ret,-1,"munmap");
    return 0;
}

// int map_gets_recv(int new_fd,char* file,pfac t,int sfd)
// {
//     //接文件大小
//     long int len=0;
//     LOG1("map recv len:");
//     recv_n(new_fd,&len,8);
//     LOG2l("map recv len:",len);
//     LOG3("opening:",file);
//     int fd=open(file,O_RDWR|O_CREAT,0666);
//     ERROR_CHECK(fd,-1,"map recv open fail");
//     ftruncate(fd,len);
//     char* p=mmap(NULL,len,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
//     //直接收
//     // LOG2("pfd=",pfd);
//     LOG1("map file recv");
//     gets_node node;
//     node.p=p;node.fd=sfd;
//     node.fd=fd;//用来装文件fd
//     for(int i=0;i<GERS_PTHREAD;i++)
//     {
//         qgets_insert_n(&t->gque,&node);
//         pthread_cond_signal(&t->gcond);
//     }
//     return 0;
// }