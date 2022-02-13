#include <func.h>


void* pthread_func(void *p)
{
    printf("I am child thread\n");
    return NULL;
}

//pthread_join 去等待子线程
int main()
{
    pthread_t pthid;
    int ret=pthread_create(&pthid,NULL,pthread_func,NULL);
    THREAD_ERR_CHECK(ret,"pthread_create");
    ret=pthread_join(pthid,NULL);
    THREAD_ERR_CHECK(ret,"pthread_join");
    printf("I am main thread\n");
    return 0;
}