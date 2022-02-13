#include <func.h>

void* thread_func(void *q)
{
    pthread_exit((void*)3);
}
//设置线程属性
int main()
{
    pthread_t pthid;
    pthread_attr_t attr;
    pthread_attr_init(&attr);//线程属性初始化
    pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);//设置线程属性为detached
    pthread_create(&pthid,&attr,thread_func,NULL);
    long thread_ret;
    int ret=pthread_join(pthid,(void**)&thread_ret);//(void**)&thread_ret
    THREAD_ERR_CHECK(ret,"pthread_join");
    printf("child thread_ret=%ld\n",thread_ret);
    return 0;
}