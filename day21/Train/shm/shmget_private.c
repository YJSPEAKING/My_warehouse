#include <func.h>
//IPC_PRIVATE每次都会创建共享内存段
int main()
{
    int shmid;
    shmid=shmget(IPC_PRIVATE,4096,IPC_CREAT|0600);
    ERROR_CHECK(shmid,-1,"shmget");
    return 0;
}