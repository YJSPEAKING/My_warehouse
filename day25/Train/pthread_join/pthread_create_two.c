#include <func.h>


void* pthread_func(void *p)
{
    printf("I am child thread %ld\n",(long)p);
    return NULL;
}

//创建两个子线程,0号线程打印我是线程0,1号线程打印我线程1
int main()
{
    pthread_t pthid[2];
    long i;
    int ret;
    for(i=0;i<2;i++)
    {
        ret=pthread_create(pthid+i,NULL,pthread_func,(void*)i);
        THREAD_ERR_CHECK(ret,"pthread_create");
    }
    //为什么打印都是2，是因为子线程去打印时，主线程把i改为2
    // for(i=0;i<2;i++)
    // {
    //     ret=pthread_join(pthid[i],NULL);
    //     THREAD_ERR_CHECK(ret,"pthread_join");
    // }
    pthread_join(pthid[0],NULL);
    pthread_join(pthid[1],NULL);
    printf("I am main thread\n");
    return 0;
}
   
    
    