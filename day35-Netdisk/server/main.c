#include"factory.h"
#include"head.h"
#include"que.h"
#include"tcp_epoll.h"
#include"sr.h"
#include"sqloper.h"
#include"oper.h"
#include<stdlib.h>
#include"md5.h"
#include"time_break.h"
int main()
{
    //IP,port,pthread_num
    int fd=open("net.config",O_RDONLY);
    char buf[526];
    read(fd,buf,sizeof(buf)); 
    char IP[20],PORT[10];
    bzero(IP,sizeof(IP));
    bzero(PORT,sizeof(PORT));
    int pthread_num,capacity;
    sscanf(buf,"%s%s%d%d",IP,PORT,&pthread_num,&capacity);
    close(fd);
    printf("%s %s %d %d\n",IP,PORT,pthread_num,capacity);
    fac_t t;
    int sfd; 
    fac_init(&t,pthread_num,capacity);
    tcp_init(&sfd,IP,PORT);
    req_t state;;
    fac_start(&t,pthread_num);
    int new_fd;
    pQue que=&t.que;
    int epfd=epoll_create(1);
    int ret=epoll_add(epfd,sfd);
    ERROR_CHECK(ret,-1,"epoll_add");


    
    struct epoll_event evs[capacity+1];
    int ready_num=0;
    struct sockaddr_in saddr;
    t.epfd=epfd;
    //维护一个断开连接的客户信息表
    client_info info[capacity+10];
    bzero(info,(capacity+10)*sizeof(client_info));
    int temp;
    int rfd=open("日志",O_RDWR|O_CREAT,0666);
    lseek(rfd,0,SEEK_END);
    time_t now;
    char name[200]={0};
    while(1)
    {
        ready_num=epoll_wait(epfd,evs,capacity+1,1000);
        for(int i=0;i<ready_num;i++)
        {
            if(sfd==evs[i].data.fd){//有新的连接
                bzero(&saddr,sizeof(saddr));
                socklen_t len=sizeof(saddr);
                LOG1("新连接来了");
                new_fd=accept(sfd,(struct sockaddr*)&saddr,&len);
                LOG1("连接");
                bzero(buf,sizeof(buf));
                usleep(3);
                ret=recv(new_fd,&temp,4,MSG_DONTWAIT);//非阻塞收
                if(ret!=-1){//收到东西,用user_id代表不同用户，这是唯一的
                    LOG2("重连,user_id=",temp);
                    for(int e=0;e<capacity+10;e++)
                    {
                        if(1==info[e].flag&&info[e].user_id==temp){
                            memcpy(&t.client[new_fd],&info[e],sizeof(client_info));//拷贝回去
                            info[e].flag=0;
                            LOG1("拷贝进新地方");
                            LOG2("code=",info[e].code);
                            break;
                        }                  
                    }
                }
                time(&now);
                bzero(buf,sizeof(buf));
                sprintf(buf,"有客户端于%s连接\n",ctime(&now));
                write(rfd,buf,sizeof(buf));
                LOG2("main sfd:",sfd);
                epoll_add(epfd,new_fd);
                t.client[new_fd].fd=new_fd;
                t.client[new_fd].flag=1;
                t.client[new_fd].circle=0;
            }
            fd=evs[i].data.fd;//记录fd
            
            if(1==t.client[fd].flag&&fd==t.client[fd].fd){//对应下标的fd相等，没登陆
            //接命令
                t.client[fd].circle=0;//先清零
                req_recv(fd,&state);
                if(REGISTER== state.req){
                    if(1==t.client[fd].login)
                    {
                        send_str_n(fd,"n");//已经登录
                        LOG1("已经登录");
                        continue;
                    }else{
                        send_str_n(fd,"y"); 
                        LOG1("没有登录");   
                    }
                    LOG1("-----------------------------------");
                    bzero(name,sizeof(name));
                    ret=s_register(&t.client[fd],name);//new_fd作为下标//注册
                    write_user(rfd,t.client[fd].user_id,"REGISTER");//写日志
                    bzero(buf,sizeof(buf));
                    sprintf(buf,"客户%s于%s注册\n",name,ctime(&now));//写日志
                    write(rfd,buf,sizeof(buf));//写日志
                    LOG1("-----------------------------------");
                    if(0==ret){
                        send_str_n(fd,"reg success");
                        LOG1("reg success");
                    }else{
                        send_str_n(fd,"reg fail");
                        LOG1("reg success");
                    }
                }
                else if(LOGIN==state.req){
                    if(1==t.client[fd].login)
                    {
                        send_str_n(fd,"n");//已经登录
                        continue;
                    }else{
                        send_str_n(fd,"y");    
                    }
                    LOG1("-----------------------------------");
                    bzero(name,sizeof(name));
                    ret=s_login(&t.client[fd],name);    
                    time(&now);
                    bzero(buf,sizeof(buf));
                    sprintf(buf,"客户%s于%s登录\n",name,ctime(&now));
                    write(rfd,buf,sizeof(buf));             
                    LOG1("-----------------------------------"); 
                    if(0==ret){
                        send_str_n(fd,"log success");
                        LOG1("log success");
                    }else{
                        send_str_n(fd,"log fail");
                        LOG1("log fail");
                        continue;
                    }
                    send(fd,&t.client[fd].user_id,4,0);
                    t.client[fd].login=1;
                    LOG2("user_id=",t.client[fd].user_id);
                }
                else if(CD==state.req){
                    LOG1("CD:-----------------------------------");
                        ret=wlogin(&t.client[fd]);
                        if(-1==ret){
                            continue;
                        }
                        LOG1("登录成功");
                        ret=token_check(fd,t.client[fd].token);
                        RETURN_INFO(ret,fd,"y","n");
                        LOG1("token success");
                        bzero(buf,sizeof(buf));//文件名
                        recv_str_n(fd,buf);  bzero(name,sizeof(name));
                        ret=cd(buf,&t.client[fd].code,t.client[fd].user_id,t.client[fd].path,name);  
                        RETURN_INFO(ret,fd,"y","n");
                        time(&now);
                        bzero(buf,sizeof(buf));
                        sprintf(buf,"客户%s于%sCD\n",name,ctime(&now));
                        write(rfd,buf,sizeof(buf));             
                        LOG1("-----------------------------------");
                }
                else if(LS==state.req){
                    LOG1("LS:-----------------------------------");
                    ret=wlogin(&t.client[fd]);
                    if(-1==ret){
                        continue;
                    }
                    ret=token_check(fd,t.client[fd].token);
                    RETURN_INFO(ret,fd,"y","n");
                    bzero(buf,sizeof(buf));
                    ls(t.client[fd].code,t.client[fd].user_id,buf);
                    //buf没东西也要发一点，不然收不到,所以先发大小
                    write_user(rfd,t.client[fd].user_id,"LS");
                    int len=strlen(buf);
                    send_n(fd,&len,4);
                    LOG2("LEN=",len);
                    if(len){
                        LOG1("有东西，发");
                        send_n(fd,buf,len);
                    }
                    time(&now);
                    bzero(buf,sizeof(buf));
                    sprintf(buf,"客户%s于%sLS\n",name,ctime(&now));
                    write(rfd,buf,sizeof(buf));             
                    LOG1("-----------------------------------");
                }
                else if(REMOVE==state.req){
                    LOG1("REMOVE-----------------------------------");
                    ret=wlogin(&t.client[fd]);///////////
                    if(-1==ret){
                        continue;//有这个东西，没封装;
                    }
                    ret=token_check(fd,t.client[fd].token);
                    RETURN_INFO(ret,fd,"y","n");///////////固定
                    bzero(buf,sizeof(buf));
                    recv_str_n(fd,buf);//收文件名
                    bzero(name,sizeof(name));
                    ret=rem(&t.client[fd],buf,name);
                    RETURN_INFO(ret,fd,"y","n");
                    time(&now);
                    bzero(buf,sizeof(buf));
                    sprintf(buf,"客户%s于%sREMOVE\n",name,ctime(&now));
                    write(rfd,buf,sizeof(buf));             
                    LOG1("-----------------------------------");
                }
                else if(PWD==state.req){
                    LOG1("PWD-----------------------------------");
                    ret=wlogin(&t.client[fd]);
                    if(-1==ret){
                        continue;
                    }
                    ret=token_check(fd,t.client[fd].token);
                    RETURN_INFO(ret,fd,"y","n");
                    send_str_n(fd,t.client[fd].path);
                    LOG1("PATH:");
                    LOG1(t.client[fd].path);
                    write_user(rfd,t.client[fd].user_id,"PWD");
                    LOG1("-----------------------------------");
                }
                else if(GETS==state.req){
                    LOG1("GETS-----------------------------------");
                    ret=wlogin(&t.client[fd]);
                    if(-1==ret){
                        continue;
                    }
                    ret=token_check(fd,t.client[fd].token);
                    RETURN_INFO(ret,fd,"y","n");
                    que_node node;
                    bzero(&node,sizeof(node));
                    node.user_id=t.client[fd].user_id;
                    node.req=GETS;
                    bzero(buf,sizeof(buf));
                    recv_str_n(fd,buf);
                    memcpy(node.file_name,buf,strlen(buf));//收文件名    
                    LOG1(node.file_name);
                    node.code=t.client[fd].code;  
                    node.fd=sfd;//方便子线程accept
                    LOG3("GETS文件:",node.file_name);
                    //这里要重新申请连接
                    pthread_mutex_lock(&t.que.mutex);
                    que_insert_n(&t.que,&node);
                    pthread_mutex_unlock(&t.que.mutex);
                    pthread_cond_signal(&t.cond);
                    write_user(rfd,t.client[fd].user_id,"GETS");
                //这样子就不需要关闭原来的epoll
                    LOG1("-----------------------------------");
                }      
                else if(PUTS==state.req){
                    LOG1("PUTS-----------------------------------");
                    ret=wlogin(&t.client[fd]);
                    if(-1==ret){
                        continue;
                    }
                    token_check(fd,t.client[fd].token);
                    RETURN_INFO(ret,fd,"y","n");
                    que_node node;
                    bzero(&node,sizeof(node));
                    node.user_id=t.client[fd].user_id;
                    node.req=PUTS;
                    node.code=t.client[fd].code;
                    bzero(buf,sizeof(buf));
                    LOG1("收文件名");
                    recv_str_n(fd,buf);
                    memcpy(node.file_name,buf,strlen(buf));//收文件名
                    LOG1(node.file_name);
                    node.fd=sfd;
                    pthread_mutex_lock(&t.que.mutex);
                    que_insert_n(&t.que,&node);
                    pthread_mutex_unlock(&t.que.mutex);
                    pthread_cond_signal(&t.cond);
                    write_user(rfd,t.client[fd].user_id,"PUTS");
                //这样子就不需要关闭原来的epoll
                    LOG1("-----------------------------------");
                }      
                else if(MKDIR==state.req){
                    LOG1("MKDIR-----------------------------------");
                    ret=wlogin(&t.client[fd]);///////////
                    if(-1==ret){
                        continue;//有这个东西，没封装;
                    }
                    ret=token_check(fd,t.client[fd].token);
                    RETURN_INFO(ret,fd,"y","n");///////////固定
                    bzero(buf,sizeof(buf));
                    recv_str_n(fd,buf);
                    makd(&t.client[fd],buf);//数据库操作失败才会失败，太烦没写
                    write_user(rfd,t.client[fd].user_id,"MKDIR");
                }      
                else if(EXIT==state.req){  
                    LOG1("EXIT-----------------------------------");
                    ret=wlogin(&t.client[fd]);///////////
                    if(0==ret){
                        ret=token_check(fd,t.client[fd].token);
                        RETURN_INFO(ret,fd,"y","n");///////////固定    
                        LOG1("下线");
                    }                
                    t.client[fd].flag=0;
                    t.client[fd].login=0;
                    epoll_del(epfd,fd);
                    close(fd);  
                    write_user(rfd,t.client[fd].user_id,"EXIT");
                }
                else{
                    printf("错误，user_id=%d被强制退出\n",t.client[fd].user_id);
                    t.client[fd].flag=0;
                    t.client[fd].login=0;
                    epoll_del(epfd,fd);
                    close(fd); 
                }    
            }
        }
        if(0==ready_num){
            LOG1("1秒");
            for(int d=0;d<capacity+10;d++){
                if(1==t.client[d].flag)//先五秒，这里加了五次
                {
                    if(0==(t.client[d].circle+1)%5){
                        epoll_del(epfd,t.client[d].fd);
                        close(t.client[d].fd);
                        t.client[d].flag=0;
                        for(int e=0;e<capacity+10;e++){
                            if(0==info[e].flag){//这个info没有使用
                                memcpy(&info[e],&t.client[d],sizeof(client_info));
                                info[e].flag=1;
                                break;
                            }
                        }
                        LOG1("断开连接");
                    }else{
                        t.client[d].circle++;
                    }
                }
            }
        }
    }
    for(int i=0;i<pthread_num;i++){
        pthread_join(t.pid[i],NULL);
    }
    close(rfd);
    return 0;
}