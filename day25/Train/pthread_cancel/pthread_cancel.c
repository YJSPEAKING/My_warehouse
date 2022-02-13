#include <func.h>


void* pthread_func(void *p)
{
    printf("I am child thread\n");
    sleep(1);
    printf("you can't see me\n");
    return NULL;
}

//创建子线程后，cancel子线程，这样子线程运行到中间就会结束
int main()
{
    pthread_t pthid;
    int ret;
    ret=pthread_create(&pthid,NULL,pthread_func,NULL);
    THREAD_ERR_CHECK(ret,"pthread_create");
    //发送cancel给子线程
    ret=pthread_cancel(pthid);
    THREAD_ERR_CHECK(ret,"pthread_cancel");
    ret=pthread_join(pthid,NULL);//等待子线程
    THREAD_ERR_CHECK(ret,"pthread_join");
    printf("I am main thread\n");
    return 0;
}