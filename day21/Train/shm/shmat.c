#include <func.h>

int main()
{
    int shmid;
    shmid=shmget(1000,4096,IPC_CREAT|0600);//第一次创建，第二次相同的key值是获取
    ERROR_CHECK(shmid,-1,"shmget");
    printf("shmid=%d\n",shmid);
    char *p=shmat(shmid,NULL,0);//共享内存连接到本进程内
    ERROR_CHECK(p,(char*)-1,"shmat");
    if(!fork())
    {
        printf("I am child %s\n",p);
        sleep(10);
        return 0;
    }else{
        strcpy(p,"hello");
        wait(NULL);
        return 0;
    }
}