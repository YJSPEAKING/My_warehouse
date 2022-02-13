#include<func.h>
#define N 10000000
int main()
{
    int shmid;
    shmid=shmget(IPC_PRIVATE,4096,IPC_CREAT|0600);
    ERROR_CHECK(shmid,-1,"shmget");
    int *num=shmat(shmid,NULL,0);
    ERROR_CHECK(num,(int*)-1,"shmid");
    num[0]=0;
    if(!fork())
    {
        for(int i=0;i<N;i++)
        {
            num[0]++;
        }
        exit(0);
    }
    else{
        for(int i=0;i<N;i++)
        {
            num[0]++;
        }
        wait(NULL);
        printf("num=%d",num[0]);
        shmctl(shmid,IPC_RMID,0);
        exit(0);
    }
}