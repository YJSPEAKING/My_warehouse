//使用计数信号量，实现生产者消费者模式
#include<func.h>

int main()
{
    int semid=semget(IPC_PRIVATE,2,IPC_CREAT|0600);
    ERROR_CHECK(semid,-1,"semget");
    unsigned short arr[2]={5,5};//初值：arr[0]为full，arr[1]为empty
    int ret=semctl(semid,0,SETALL,arr);
    ERROR_CHECK(ret,-1,"semctl_init");
    if(!fork())//子进程做生产者
    {
        struct sembuf P,V;
        P.sem_num=1;
        P.sem_op=-1;//生产者P(empty)
        P.sem_flg=0;
        V.sem_num=0;//V(full)
        V.sem_op=1;
        V.sem_flg=0;
        while(1)
        {
            printf("生产者等待生产许可...full=%d,emty=%d\n",semctl(semid,0,GETVAL),semctl(semid,1,GETVAL));
            semop(semid,&P,1);
            printf("生产中...\n");
            semop(semid,&V,1);
            printf("生产结束...          full=%d,emty=%d\n",semctl(semid,0,GETVAL),semctl(semid,1,GETVAL));
            sleep(1);
        }
    }
    else//父进程做消费者
    {
        struct sembuf P,V;
        P.sem_num=0;
        P.sem_op=-1;//消费者P(full)
        P.sem_flg=0;
        V.sem_num=1;
        V.sem_op=1;//V(empty)
        V.sem_flg=0;
        while(1)
        {
            printf("消费者等待取货许可...full=%d,emty=%d\n",semctl(semid,0,GETVAL),semctl(semid,1,GETVAL));
            semop(semid,&P,1);
            printf("取货中...\n");
            semop(semid,&V,1);
            printf("取货结束...          full=%d,emty=%d\n",semctl(semid,0,GETVAL),semctl(semid,1,GETVAL));
            sleep(1);
        }
    }
}