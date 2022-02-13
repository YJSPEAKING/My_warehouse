#include <func.h>
//清理函数
void cleanup(void *p)
{
    free(p);
    printf("I am cleanup\n");
}

void* pthread_func(void *p)
{
    char *q=(char*)malloc(20);
    pthread_cleanup_push(cleanup,q);
    printf("malloc success\n");
    sleep(1);
    printf("start free\n");
    pthread_exit(NULL);//在线程退出时，会检查清理函数栈内是否有清理函数
    pthread_cleanup_pop(0);//pop(1)清理函数并执行，pop(0)弹出清理函数不执行
    return NULL;
}

//创建子线程后，子线程先malloc空间，然后再free之前，被cancel掉
int main()
{
    pthread_t pthid;
    int ret;
    ret=pthread_create(&pthid,NULL,pthread_func,NULL);
    THREAD_ERR_CHECK(ret,"pthread_create");
    //cancel时，子线程并没有开始free对应的空间
    // ret=pthread_cancel(pthid);
    // THREAD_ERR_CHECK(ret,"pthread_cancel");
    ret=pthread_join(pthid,NULL);//等待子线程
    THREAD_ERR_CHECK(ret,"pthread_join");
    printf("I am main thread\n");
    return 0;
}