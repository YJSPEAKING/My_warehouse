#include"que.h"
#include"sr.h"
#include"factory.h"
#include"oper.h"
#include"sqloper.h"
#include"tcp_epoll.h"

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
//     pfac t=(pfac)p;
//     gets_node node;
//     struct sockaddr saddr;
//     while(1)
//     {
//         LOG1("锁");
//         pthread_mutex_lock(&t->gque.mutex);
//         if(0==t->gque.size) {
//             pthread_cond_wait(&t->gcond,&t->gque.mutex);
//             LOG1("解锁");
//         }
//         qgets_get_n(&t->gque,&node);
//         pthread_mutex_unlock(&t->gque.mutex);
//         bzero(&saddr,sizeof(saddr));
//         socklen_t len=sizeof(saddr);
//         LOG1("GETS:新连接");
//         LOG2("sfd:",node.fd);
//         int afd=accept(node.fd,(struct sockaddr*)&saddr,&len);   
//         send_n(afd,&node.start,8);//先发起始位置，长度
//         long slen=node.end-node.start+1;
//         send_n(afd,&slen,8);
//         send_n(afd,node.p+node.start,slen);//从start开始发
//         munmap(p+node.start,slen);
//         close(afd);
//     }
// }
void* child_gpfunc(void* p)
{
    int ret;
    pfac t=(pfac)p;
    que_node qnode;
    struct sockaddr_in saddr;
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
        LOG1("得到node");
        bzero(&saddr,sizeof(saddr));
        socklen_t len=sizeof(saddr);
        LOG1("GETS:新连接");
        LOG2("sfd:",qnode.fd);
        int afd=accept(qnode.fd,(struct sockaddr*)&saddr,&len);    
        LOG1("成功accept");
        LOG2("port=",saddr.sin_port);
        int sfd=qnode.fd;
        qnode.fd=afd;
        LOG2("外面的fd=",afd);
        if(GETS==qnode.req){
            LOG1("子线程启动下载");
            LOG3("子线程file name:",qnode.file_name);
            sleep(5);
            ret=s_gets(&qnode);
            if(-1==ret){
                send_str_n(afd,"n");
                LOG1("GETS fail");
            }else{
                send_str_n(afd,"y");
                LOG1("GETS success");
            }
        }
        else if(PUTS==qnode.req){
            LOG1("子线程启动上传");
            LOG3("子线程file name:",qnode.file_name);
            ret=s_puts(&qnode);
            if(-1==ret){
                send_str_n(afd,"n");
                LOG1("PUTS fail");              
            }else{
                send_str_n(afd,"y");
                LOG1("PUTS success");
            }
       }  
       close(afd);
    }
}

//weather log in
int wlogin(CInfo t)
{
    if(1==t->login){
        send_str_n(t->fd,"y");//已经登录
        return 0;
    }else{
        send_str_n(t->fd,"n");    
        return -1;          
    }
}

int token_check(int fd,char* token)
{
    char buf[50]={0};
    recv_str_n(fd,buf);
    if(0==strcmp(token,buf)){
        return 0;
    }else{
        return -1;
    }
}