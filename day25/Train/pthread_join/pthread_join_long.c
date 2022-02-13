#include <func.h>


void* pthread_func(void *p)
{
    printf("I am child thread\n");
    // return (void*)5;
    pthread_exit((void*)5);//pthread_exit传给它的值就是返回值
}

//pthread_join 去等待子线程，接收到一个长整型值,来判断子线程是否执行成功
int main()
{
    pthread_t pthid;
    int ret=pthread_create(&pthid,NULL,pthread_func,NULL);
    THREAD_ERR_CHECK(ret,"pthread_create");
    long thread_return;//定义一个long类型，不要是int
    ret=pthread_join(pthid,(void**)&thread_return);
    THREAD_ERR_CHECK(ret,"pthread_join");
    printf("I am main thread,child return=%ld\n",thread_return);
    return 0;
}