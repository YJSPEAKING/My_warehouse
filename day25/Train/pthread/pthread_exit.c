#include <func.h>

void print()
{
    pthread_exit(NULL);
}

void* pthread_func(void *p)
{
    printf("I am child thread,%ld\n",pthread_self());
    print();
    printf("after print\n");
    return NULL;
}
//子线程的退出方式，两种 1、线程函数return  2、任何一个函数调用pthread_exit
//任何一个线程调用exit，都会造成进程终止
int main()
{
    pthread_t pthid;
    int ret=pthread_create(&pthid,NULL,pthread_func,NULL);
    THREAD_ERR_CHECK(ret,"pthread_create")
    sleep(1);
    printf("I am main thread\n");
    return 0;
}
