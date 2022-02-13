//两个进程对一个共享内存各加1000万，通过pv操作，实现最终结果是2千万
#include<func.h>
#define N 10000000

int main()
{
    time_t start,end;
    int shmid;
    shmid=shmget(1000,4096,IPC_CREAT|0600);
    ERROR_CHECK(shmid,-1,"shmget")
    int *p=shmat(shmid,NULL,0);
    ERROR_CHECK(p,(int*)-1,"shmat")
    int ret;
    int semid=semget(1000,1,IPC_CREAT|0600);
    ERROR_CHECK(semid,-1,"semget")
    ret=semctl(semid,0,SETVAL,1);//设置初始值为1
    ERROR_CHECK(ret,-1,"semctl")
    struct sembuf P,V;
    P.sem_num=0;//P和V都是对0号信号量做操作
    P.sem_op=-1;//P是让资源数减一
    P.sem_flg=SEM_UNDO;
    V.sem_num=0;
    V.sem_op=1;
    V.sem_flg=SEM_UNDO;
    start=time(NULL);
    if(!fork())
    {
        for(int i=0;i<N;i++)
        {
            semop(semid,&P,1);
            p[0]++;
            semop(semid,&V,1);
        }
        ret=shmdt(p);
        ERROR_CHECK(ret,-1,"shmdt")
        exit(0);
    }
    else
    {
        for(int i=0;i<N;i++)
        {
            semop(semid,&P,1);
            p[0]++;
            semop(semid,&V,1);
        }
        wait(NULL);
        end=time(NULL);
        printf("%d,time=%ld\n",p[0],end-start);
        ret=shmctl(shmid,IPC_RMID,NULL);
        ERROR_CHECK(ret,-1,"shmctl")
        exit(0);
    }
}