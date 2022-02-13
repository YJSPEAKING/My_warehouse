#include<func.h>

int main()
{
    int msqid=msgget(1,IPC_CREAT|0600);
    ERROR_CHECK(msqid,-1,"msgget")
    sleep(10);
    int ret= msgctl(msqid,IPC_RMID,NULL);
    ERROR_CHECK(ret,-1,"msgctl")
    return 0;
}