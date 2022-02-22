#include "head.h"
#include"que.h"
#include"sr.h"
int main(int argc,char** argv)
{
    ARGS_CHECK(argc,3);
    int sfd;
    sfd=socket(AF_INET,SOCK_STREAM,0);//初始化一个网络描述符，对应了一个缓冲区
    ERROR_CHECK(sfd,-1,"socket");
    printf("sfd=%d\n",sfd);
    struct sockaddr_in ser_addr;
    bzero(&ser_addr,sizeof(ser_addr));//清空
    ser_addr.sin_family=AF_INET;//代表要进行ipv4通信
    ser_addr.sin_addr.s_addr=inet_addr(argv[1]);//把ip的点分十进制转为网络字节序
    ser_addr.sin_port=htons(atoi(argv[2]));//把端口转为网络字节序
    //客户端就要去连接服务器
    int ret=connect(sfd,(struct sockaddr *)&ser_addr,sizeof(ser_addr));
    ERROR_CHECK(ret,-1,"connect");

    client_info p;
    p.fd=sfd;
    fac_t d;//直接复用，有一些冗余信息
    fac_init(&d,20,50);
    fac_start(&d,20);
    //接收文件名
    printf("connect\n");
    char user_name[50]={0};
    while(1)
    {
        req_t t;
        char buf[526]={0};
        printf("%s:",user_name);
        fflush(stdout);
        scanf("%s",buf);//getline可以尝试优化
        LOG1(buf);
        if(0==strcmp(buf,"cd")){
            ret=w_connect(&sfd);
            if(0==ret){
                ret=connect(sfd,(struct sockaddr *)&ser_addr,sizeof(ser_addr));
                ERROR_CHECK(ret,-1,"connect");
                send(sfd,&p.user_id,4,0);
            }
            ret=clogin(p.fd,CD);//是否登录
            if(-1==ret){
                continue;
            }
            send_str_n(p.fd,p.token);//发token
            bzero(buf,sizeof(buf));
            recv_str_n(p.fd,buf);
            if(0==strcmp(buf,"y")){
                LOG1("token success");
            }
            else{
                printf("token error\n");
                continue;
            }
            
            //cd是否成功
            bzero(buf,sizeof(buf));
            scanf("%s",buf);
            send_str_n(p.fd,buf);
            bzero(buf,sizeof(buf));
            recv_str_n(p.fd,buf);
            if(0==strcmp(buf,"n")){
                printf("cd error\n");
                continue;
            }
            LOG1("cd success");
        }else if(0==strcmp(buf,"ls")){
            ret=w_connect(&sfd);
            if(0==ret){
                ret=connect(sfd,(struct sockaddr *)&ser_addr,sizeof(ser_addr));
                ERROR_CHECK(ret,-1,"connect");
                LOG2("user_id=",p.user_id);
                send(sfd,&p.user_id,4,0);
            }
            ret=clogin(p.fd,LS);//是否登录
            if(-1==ret){
                continue;
            }  
            send_str_n(p.fd,p.token);//发token
            bzero(buf,sizeof(buf));
            recv_str_n(p.fd,buf);
            if(0==strcmp(buf,"y")){
                LOG1("token success");
            }
            else{
                printf("token error\n");
                continue;
            }
            
            bzero(buf,sizeof(buf));
            int len;
            recv_n(p.fd,&len,4);
            if(len){
                LOG2("len=",len);
                recv_n(p.fd,buf,len);//收ls的信息
                printf("%s\n",buf);
            }
        }else if(0==strcmp(buf,"remove")){
            ret=w_connect(&sfd);
            if(0==ret){
                ret=connect(sfd,(struct sockaddr *)&ser_addr,sizeof(ser_addr));
                ERROR_CHECK(ret,-1,"connect");
                send(sfd,&p.user_id,4,0);
            }
            ret=clogin(p.fd,REMOVE);//是否登录//////
            if(-1==ret){
                continue;
            }  
            send_str_n(p.fd,p.token);//发token
            bzero(buf,sizeof(buf));
            recv_str_n(p.fd,buf);
            if(0==strcmp(buf,"y")){
                LOG1("token success");
            }
            else{
                printf("token error\n");
                continue;
            }
             //////////固定
            bzero(buf,sizeof(buf));
            scanf("%s",buf);
            send_str_n(p.fd,buf);
            bzero(buf,sizeof(buf));
            recv_str_n(p.fd,buf);
            if(0==strcmp(buf,"y")){}
            else{
                printf("rm error\n");
            }
        }else if(0==strcmp(buf,"pwd")){
            ret=w_connect(&sfd);
            if(0==ret){
                ret=connect(sfd,(struct sockaddr *)&ser_addr,sizeof(ser_addr));
                ERROR_CHECK(ret,-1,"connect");
                send(sfd,&p.user_id,4,0);
            }
            ret=clogin(p.fd,PWD);//是否登录//////
            if(-1==ret){
                continue;
            }  
            send_str_n(p.fd,p.token);//发token
            bzero(buf,sizeof(buf));
            recv_str_n(p.fd,buf);
            if(0==strcmp(buf,"y")){
                LOG1("token success");
            }
            else{
                printf("token error\n");
                continue;
            }
             //////////固定
            bzero(buf,sizeof(buf));
            recv_str_n(p.fd,buf);
            printf("%s\n",buf);
        }else if(0==strcmp(buf,"mkdir")){
            ret=w_connect(&sfd);
            if(0==ret){
                ret=connect(sfd,(struct sockaddr *)&ser_addr,sizeof(ser_addr));
                ERROR_CHECK(ret,-1,"connect");
                send(sfd,&p.user_id,4,0);
            }
            ret=clogin(p.fd,MKDIR);//是否登录//////
            if(-1==ret){
                continue;
            }  
            send_str_n(p.fd,p.token);//发token
            bzero(buf,sizeof(buf));
            recv_str_n(p.fd,buf);
            if(0==strcmp(buf,"y")){
                LOG1("token success");
            }
            else{
                printf("token error\n");
                continue;
            }
             //////////固定
            bzero(buf,sizeof(buf));
            scanf("%s",buf);
            send_str_n(p.fd,buf);
            LOG1("mkdir has been send");
        }else if(0==strcmp(buf,"register")){
            ret=w_connect(&sfd);
            if(0==ret){
                ret=connect(sfd,(struct sockaddr *)&ser_addr,sizeof(ser_addr));
                ERROR_CHECK(ret,-1,"connect");
                send(sfd,&p.user_id,4,0);
            }
            t.req=REGISTER;
            LOG1("reg ing");
            req_send(p.fd,&t);
            bzero(buf,sizeof(buf));
            recv_str_n(p.fd,buf);
            if(0==strcmp(buf,"n")){
                printf("已经登录，禁止注册\n");
                continue;
            }         
            LOG1("已经发送");
            c_register(&p);
            bzero(buf,sizeof(buf));
            recv_str_n(p.fd,buf);
            printf("%s\n",buf);
        }else if(0==strcmp(buf,"login")){
            ret=w_connect(&sfd);
            if(0==ret){
                ret=connect(sfd,(struct sockaddr *)&ser_addr,sizeof(ser_addr));
                ERROR_CHECK(ret,-1,"connect");
                send(sfd,&p.user_id,4,0);
            }
            t.req=LOGIN;
            req_send(p.fd,&t);
            bzero(buf,sizeof(buf));
            recv_str_n(p.fd,buf);
            if(0==strcmp(buf,"n")){
                printf("已经登录\n");
                continue;
            }
            c_login(&p,user_name);
            recv_str_n(p.fd,buf);
            LOG1(buf);
            recv(p.fd,&p.user_id,4,0);
        }else if(0==strcmp(buf,"gets")){
            ret=w_connect(&sfd);
            if(0==ret){
                ret=connect(sfd,(struct sockaddr *)&ser_addr,sizeof(ser_addr));
                ERROR_CHECK(ret,-1,"connect");
                send(sfd,&p.user_id,4,0);
            }
            ret=clogin(p.fd,GETS);//是否登录//////
            if(-1==ret){
                continue;
            }  
            send_str_n(p.fd,p.token);//发token
            bzero(buf,sizeof(buf));
            recv_str_n(p.fd,buf);
            if(0==strcmp(buf,"y")){
                LOG1("token success");
            }
            else{
                printf("token error\n");
                continue;
            }
             //////////固定
            que_node node;//塞进队列
            bzero(node.file_name,200);
            scanf("%s",node.file_name);
            send_str_n(p.fd,node.file_name);//发文件名
            //新连接
            node.req=GETS;
            memcpy(&node.addr,&ser_addr,sizeof(ser_addr));
            pthread_mutex_lock(&d.que.mutex);
            //塞进去
            que_insert_n(&d.que,&node);
            pthread_mutex_unlock(&d.que.mutex);
            pthread_cond_signal(&d.cond);
        }else if(0==strcmp(buf,"puts")){
            ret=w_connect(&sfd);
            if(0==ret){
                ret=connect(sfd,(struct sockaddr *)&ser_addr,sizeof(ser_addr));
                ERROR_CHECK(ret,-1,"connect");
                send(sfd,&p.user_id,4,0);
            }
            que_node node;
            bzero(&node,sizeof(que_node));
            scanf("%s",node.file_name);
            if(-1==(ret=open(node.file_name,O_RDONLY,0666))){
                printf("没有这个文件\n");
                continue;
            }
            close(ret);
            ret=clogin(p.fd,PUTS);//是否登录//////
            if(-1==ret){
                continue;
            }  
            send_str_n(p.fd,p.token);//发token
            bzero(buf,sizeof(buf));
            recv_str_n(p.fd,buf);
            if(0==strcmp(buf,"y")){
                LOG1("token success");
            }
            else{
                printf("token error\n");
                continue;
            } //////////固定
            //发文件名
            send_str_n(p.fd,node.file_name);
            node.req=PUTS;
            memcpy(&node.addr,&ser_addr,sizeof(ser_addr));
            LOG2("main port:",ntohs(node.addr.sin_port));
            pthread_mutex_lock(&d.que.mutex);
            //塞进去
            que_insert_n(&d.que,&node);
            pthread_mutex_unlock(&d.que.mutex);
            pthread_cond_signal(&d.cond);
        }
        else if(0==strcmp(buf,"exit")){
            ret=w_connect(&sfd);
            if(0==ret){
                ret=connect(sfd,(struct sockaddr *)&ser_addr,sizeof(ser_addr));
                ERROR_CHECK(ret,-1,"connect");
                send(sfd,&p.user_id,4,0);
            }
            ret=clogin(p.fd,EXIT);//是否登录//////
            if(-1==ret){
                break;//exit专有
            }  
            send_str_n(p.fd,p.token);//发token
            bzero(buf,sizeof(buf));
            recv_str_n(p.fd,buf);
            if(0==strcmp(buf,"y")){
                LOG1("token success");
            }
            else{
                printf("token error\n");
                continue;
            } //////////固定
            close(p.fd);
            break;
        }else{
            printf("error message\n");
        }
    bzero(buf,sizeof(buf));

    }

    close(sfd);
    return 0;
}