//创建一个子线程，主线程cancel子线程
#include<func.h>

void* func(void* p)
{
    printf("盲猜咱看不到这句话\n");
    return NULL;
}

int main()
{
    
    pthread_t pthid;
    int ret=pthread_create(&pthid,NULL,func,NULL);
    THREAD_ERR_CHECK(ret,"creat")
    ret=pthread_cancel(pthid);
    THREAD_ERR_CHECK(ret,"cancel")
    printf("主进程结束\n");
    return 0;
}