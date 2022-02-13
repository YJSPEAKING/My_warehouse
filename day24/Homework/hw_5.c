//创建一个子线程，在子线程中使用堆空间，改变数据，主线程打印，和上课一致
#include<func.h>

void* func(void *p)
{
    strcpy(p,"hello");
    printf("子线程完事啦\n");
    return NULL;
}

int main()
{
    pthread_t pthid;
    char *p=(char*)malloc(10);//主线程申请堆空间
    int ret=pthread_create(&pthid,NULL,func,p);
    THREAD_ERR_CHECK(ret,"creat")
    usleep(1);//不睡一下子线程来不及干活就结束了
    printf("%s\n",p);
    free(p);
    return 0;
}