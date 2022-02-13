#include<func.h>
int main()
{
    int shmid;
    shmid=shmget(IPC_PRIVATE,4096,IPC_CREAT|0600);
    ERROR_CHECK(shmid,-1,"shmget");
    printf("shmid=%d\n",shmid);
    char *p=shmat(shmid,NULL,0);//进程连入共享内存
    ERROR_CHECK(p,(char*)-1,"shmat")
    if(!fork())
    {
        printf("message from shared memory:%s\n",p);
        sleep(10);
        shmctl(shmid,IPC_RMID,0);
        exit(0);
    }
    else{
        strcpy(p,"How are you");
        wait(NULL);
        exit(0);
    }
}