#include <func.h>


void* pthread_func(void *p)
{
    printf("I am child thread\n");
    p=malloc(20);
    strcpy((char*)p,"hello");
    return p;
}

//pthread_join 去等待子线程,pthread_join去接一个指针的返回值
int main()
{
    pthread_t pthid;
    int ret=pthread_create(&pthid,NULL,pthread_func,NULL);
    THREAD_ERR_CHECK(ret,"pthread_create");
    char *p;//定义一个一级指针去接子线程的返回值
    ret=pthread_join(pthid,(void**)&p);
    THREAD_ERR_CHECK(ret,"pthread_join");
    printf("I am main thread,gets=%s\n",p);
    return 0;
}