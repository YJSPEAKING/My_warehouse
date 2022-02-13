//通过mkfifo命令新建两个管道文件1.fifo，2.fifo，然后两个进程通过管道文件实现即时聊天效果，就是双方想说就说（用上select）
#include <func.h>
//角色：男孩
int main(int argc,char* argv[])
{
    ARGS_CHECK(argc,3);
    int fdr=open(argv[1],O_RDONLY);
    ERROR_CHECK(fdr,-1,"open_r");
    int fdw=open(argv[2],O_WRONLY);
    ERROR_CHECK(fdw,-1,"open_w");
    printf("【我】进入聊天室\n");
    char buf[128]={0};
    fd_set rdset;
    int ret;
    int ready_fdnum;
    while(1)
    {
        FD_ZERO(&rdset);//要记得取地址
        FD_SET(STDIN_FILENO,&rdset);
        FD_SET(fdr,&rdset);
        ready_fdnum=select(fdr+1,&rdset,NULL,NULL,NULL);
        if(FD_ISSET(STDIN_FILENO,&rdset))
        {
            memset(buf,0,sizeof(buf));
            ret=read(STDIN_FILENO,buf,sizeof(buf));
            //男孩离开
            if(ret==0)
            {
                printf("【我】离开了聊天室\n");
                break;
            }
            write(fdw,buf,strlen(buf)-1);
        }
        if(FD_ISSET(fdr,&rdset))
        {
            memset(buf,0,sizeof(buf));
            ret=read(fdr,buf,sizeof(buf));
            //女孩离开
            if(ret==0)
            {
                printf("【女孩】离开了聊天室\n");
                break;
            }
            printf("【女孩】：%s\n",buf);
        }
    }
    close(fdr);
    close(fdw);
    return 0;
}