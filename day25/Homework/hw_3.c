//创建一个子线程，cancel子线程，在子线程中push两个清理函数，感受清理函数的执行顺序
#include<func.h>

void cleanup(void *p)
{
    printf("%ld cleaned\n",(long)p);
}
void* func(void *p)
{
    pthread_cleanup_push(cleanup,(void*)1);
    pthread_cleanup_push(cleanup,(void*)2);
    sleep(5);
    printf("看不到我\n");
    pthread_cleanup_pop(1);
    pthread_cleanup_pop(1);
    printf("cleanup success\n");
    return NULL;
}

int main()
{
    pthread_t pthid;
    int ret=pthread_create(&pthid,NULL,func,NULL);
    THREAD_ERR_CHECK(ret,"create")
    ret=pthread_cancel(pthid);
    THREAD_ERR_CHECK(ret,"cancel"); 
    printf("cancel success\n");  
    ret=pthread_join(pthid,NULL);//要等一下子进程
    return 0;
}