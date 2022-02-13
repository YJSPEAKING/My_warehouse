#include <func.h>
void Daemon()
{
    if(fork())//创建子进程，父进程退出
    {
        exit(0);
    }
    setsid();//成立新会话
    chdir("/");//改名路径到根
    umask(0);//修改文件掩码
    int i;
    for(i=0;i<3;i++)
    {
        close(i);
    }
}

//创建daemon进程
int main()
{
    Daemon();
    while(1)
    {
        sleep(1);
    }
    return 0;
}