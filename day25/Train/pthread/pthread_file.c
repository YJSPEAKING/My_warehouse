#include <func.h>

void* pthread_func(void *p)
{
    int fd=*(int*)p;
    close(fd);
    printf("I am child thread\n");
}

//主线程和子线程任何一个线程关闭了文件后，其他线程就读不了
int main()
{
    pthread_t pthid;
    int fd=open("file",O_RDWR);
    ERROR_CHECK(fd,-1,"open");
    int ret=pthread_create(&pthid,NULL,pthread_func,&fd);
    THREAD_ERR_CHECK(ret,"pthread_create")
    sleep(1);
    printf("I am main thread\n");
    char buf[128]={0};
    ret=read(fd,buf,sizeof(buf));
    printf("I am main thread,ret=%d,%s\n",ret,buf);
    return 0;
}