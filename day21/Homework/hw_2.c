#include<func.h>
int main()
{
    int fds[2];//0读1写
    int ret=pipe(fds);
    ERROR_CHECK(ret,-1,"pipe")
    char buf[128]={0};
    if(!fork())
    {
        close(fds[0]);//子进程把读关了
        write(fds[1],"Hello",5);
        wait(NULL);
        close(fds[1]);
    }
    else{
        close(fds[1]);
        read(fds[0],buf,sizeof(buf));
        printf("Father gets:%s\n",buf);
        close(fds[0]);
        exit(0);
    }
}