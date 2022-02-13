//创建一个子线程，在子线程中使用main的栈空间，改变数据，主线程打印，和上课一致
#include<func.h>

void* func(void *p)
{
    int* q=(int*)p;
    *q=5;
    printf("子线程完事啦\n");
    return NULL;
}

int main()
{
    pthread_t pthid;
    int i=10;
    int ret=pthread_create(&pthid,NULL,func,&i);
    THREAD_ERR_CHECK(ret,"creat")
    usleep(1);//不睡一下子线程来不及干活就结束了
    printf("%d\n",i);
    return 0;
}