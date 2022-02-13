#include <func.h>

int main()
{
    int shmid;
    shmid=shmget(1000,4096,IPC_CREAT|0600);
    ERROR_CHECK(shmid,-1,"shmget");
    struct shmid_ds buf;
    //获取共享内存的属性信息
    int ret=shmctl(shmid,IPC_STAT,&buf);
    ERROR_CHECK(ret,-1,"shmctl");
    printf("cuid=%d,mode=%o,size=%ld,attach=%ld\n",buf.shm_perm.cuid,\
    buf.shm_perm.mode,buf.shm_segsz,buf.shm_nattch);
    return 0;
}