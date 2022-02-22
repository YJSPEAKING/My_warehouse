#include"que.h"
#include"factory.h"
#include"sr.h"

int recv_fd(int sfd,int *fd)
{
    int ret;
    struct iovec iov[1];
    char buf[128];
    iov[0].iov_base=buf;
    iov[0].iov_len=5;
    struct msghdr hdr;
    bzero(&hdr,sizeof(hdr));
    int clen=CMSG_LEN(sizeof(int)); 
    struct cmsghdr *cmsg=(struct cmsghdr *)malloc(clen);
    bzero(cmsg,clen);
    cmsg->cmsg_level=SOL_SOCKET;
    cmsg->cmsg_type=SCM_RIGHTS;   
    cmsg->cmsg_len=clen;
    hdr.msg_iov=iov;
    hdr.msg_iovlen=1;
    hdr.msg_control=cmsg;
    hdr.msg_controllen=clen;
    recvmsg(sfd,&hdr,0);
    ERROR_CHECK(ret,-1,"recvmsg");
    *fd=*(int *)(CMSG_DATA(cmsg));
    printf("child fd:%d\n",*fd);
    return 0;
}
//做一种仪式，让内核控制信息发生进程间的dup机制
int send_fd(int sfd,int fd)
{
    int ret;
    struct iovec iov[1];
    char buf[128]="12345";
    iov[0].iov_base=buf;
    iov[0].iov_len=5;
    struct msghdr hdr;
    bzero(&hdr,sizeof(hdr));
    int clen=CMSG_LEN(sizeof(int));
    struct cmsghdr *cmsg=(struct cmsghdr *)malloc(clen);
    bzero(cmsg,clen);
    cmsg->cmsg_level=SOL_SOCKET;
    cmsg->cmsg_type=SCM_RIGHTS;  
    *(int *)(CMSG_DATA(cmsg))=fd;
    cmsg->cmsg_len=clen;
    hdr.msg_iov=iov;
    hdr.msg_iovlen=1;
    hdr.msg_control=cmsg;
    hdr.msg_controllen=clen;
    sendmsg(sfd,&hdr,0);
    ERROR_CHECK(ret,-1,"sendmsg");
    return 0;
}
//发送文件给客户端
int tran_file(int new_fd,char* file)
{
    train_t t;
    t.data_len=strlen(file);
    strcpy(t.buf,file);
    send_n(new_fd,&t,4+t.data_len);
    struct stat status;
    int fd=open(file,O_RDWR);
    ERROR_CHECK(fd,-1,"文件无法打开（不存在）");
    stat(file,&status);
    t.data_len=status.st_size;
    send_n(new_fd,&t,4);
    while(t.data_len=read(fd,t.buf,sizeof((t.buf))))
    {
        send_n(new_fd,&t,4+t.data_len);
    }
    t.data_len=0;
    send_n(new_fd,&t,4+t.data_len);
}
//不传文件名
int send_file(int new_fd,char* file)
{
    train_t t;
    struct stat status;
    LOG1(file);
    int fd=open(file,O_RDONLY,0666);
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
    char buf[350]={0};
    sprintf(buf,"%s.part",file);//拼接断点续传记录的文件
    int afd=open(buf,O_RDWR,0666);//尝试打开part
    
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
//已知大小，buf装得下
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

int tran_file_n(int new_fd,OPER req,char* file)
{
    train_nt t;
    t.data_len=strlen(file);
    strcpy(t.buf,file);
    t.req=req;
    send_n(new_fd,&t,4+sizeof(req)+t.data_len);//文件名
    struct stat status;
    int fd=open(file,O_RDWR);
    stat(file,&status);
    t.data_len=status.st_size;   
    send_n(new_fd,&t,4);
    while(t.data_len=read(fd,t.buf,sizeof((t.buf))))
    {
        send_n(new_fd,&t,4+sizeof(t.req)+t.data_len);
    }
    t.data_len=0;
    send_n(new_fd,&t,4+sizeof(t.req)+t.data_len);
}

// int send_file_n(int new_fd,char* file)
// {
//     train_nt t;
//     t.data_len=strlen(file);
// }

// int recv_file_n(int new_fd,OPER req,char* file)
// {
//     train_nt t;
//     t.data_len=strlen(file);
//     strcpy(t.buf,file);
//     t.req=req;
//     send_n(new_fd,&t,4+sizeof(req)+t.data_len);//文件名
//     struct stat status;
//     int fd=open(file,O_RDWR);
//     stat(file,&status);
//     t.data_len=status.st_size;   
//     send_n(new_fd,&t,4);
//     while(t.data_len=read(fd,t.buf,sizeof((t.buf))))
//     {
//         send_n(new_fd,&t,4+sizeof(t.req)+t.data_len);
//     }
//     t.data_len=0;
//     send_n(new_fd,&t,4+sizeof(t.req)+t.data_len);
// }

int send_str_n(int new_fd,char* buf)
{
    int len=strlen(buf),ret;    
    ret=send_n(new_fd,&len,4);
    LOG2("send len:",len);
    ERROR_CHECK(ret,-1,"send_n");
    ret=send_n(new_fd,buf,len);
    ERROR_CHECK(ret,-1,"send_n");
    return 0;
}

int recv_str_n(int new_fd,char* buf)
{
    int len,ret;
    ret=recv_n(new_fd,&len,4);
    LOG2("recv len:",len);
    ERROR_CHECK(ret,-1,"recv_n");
    ret=recv_n(new_fd,buf,len);
    ERROR_CHECK(ret,-1,"recv_n");
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
    send_n(new_fd,&len,8);//发送文件大小，fturncat直接建立
    LOG1("map send len finish:");
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
            printf("进度:%6.2lf%%,total=%ld\r",(double)total/data_size*100,total);//total越来越大，格式不用管
            fflush(stdout);
        }
    }
    if(total==data_size){
        printf("进度:100.00%%\n");
    }
    LOG1("recv_map接收完毕");
    return 0;
}
//多服务器下载
// int map_gets_send(int new_fd,char* file,pfac t,int sfd)
// {
//     long int ret;
//     struct stat status;
//     LOG3("opening:",file);
//     int fd=open(file,O_RDWR,0666);//打开文件
//     ERROR_CHECK(fd,-1,"map send open");
//     stat(file,&status);
//     long int len=status.st_size;   
//     LOG2l("map sending len:",len);
//     ret=send_n(new_fd,&len,8);//发送文件大小，fturncat直接建立
//     LOG1("map send len finish:");
//     ERROR_CHECK(ret,-1,"len");
//     char* p=mmap(NULL,len,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);//mmap
//     long plen=len/GERS_PTHREAD;
//     long last=0,now=0;
//     gets_node gnode;
//     bzero(&gnode,sizeof(gets_node));
//     gnode.fd=sfd;gnode.p=p;
//     gnode.fd=sfd;
//     pthread_mutex_lock(&t->gque.mutex);
//     if(len>100){//太小没必要，bug多，规避掉
//         for(int i=1;i<GERS_PTHREAD;i++)//加GERS_PTHREAD-1次
//         {   
//             now+=plen;
//             gnode.start=last;gnode.end=now;
//             qgets_insert_n(&t->gque,&gnode);
//             last=now+1;
//         }
//         gnode.start=last;
//         gnode.end=len-1;
//         qgets_insert_n(&t->gque,&gnode);
//     }else{
//         gnode.start=0,gnode.end=len-1;
//         qgets_insert_n(&t->gque,&gnode);
//     }
//     pthread_mutex_unlock(&t->gque.mutex);
//     if(len>100){
//         for(int i=0;i<GERS_PTHREAD;i++){
//             pthread_cond_signal(&t->gcond);
//         }
//     }else{
//         pthread_cond_signal(&t->gcond);
//     }
//     return 0;
// }