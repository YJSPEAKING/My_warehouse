//创建一个子线程，传入数值1，在子线程中能够获取并打印，子线程退出，返回数值2，主线程通过pthread_join获取等待子线程结束并获取子线程的退出值并打印
#include<func.h>

void* func(void* p)
{
    printf("get from main thread:%ld\n",(long)p);
    return (void*)2;
}

int main()
{
    long func_ret;//long和void*长度一致，避免访问越界
    pthread_t pthid;
    int ret=pthread_create(&pthid,NULL,func,(void*)1);//创建一个子线程，传入参数1
    THREAD_ERR_CHECK(ret,"creat")
    ret=pthread_join(pthid,(void**)&func_ret);//func_ret作为传出参数，接收子线程终止的返回值
    THREAD_ERR_CHECK(ret,"join")
    printf("func_ret=%ld\n",func_ret);
    return 0;
}