//启动子线程，处于wait状态，主线程signal唤醒子线程
#include<func.h>

struct Node{
    pthread_mutex_t mutex;
    pthread_cond_t cond;
};

void* func(void *p)
{
    struct Node *q=(struct Node*)p;
    printf("子线程开始等待\n");
    pthread_mutex_lock(&q->mutex);
    int ret=pthread_cond_wait(&q->cond,&q->mutex);
    pthread_mutex_unlock(&q->mutex);
    printf("我回来啦%d\n",ret);
    pthread_exit(NULL);
}

int main()
{
    struct Node t;
    int ret=pthread_mutex_init(&t.mutex,NULL);//初始化锁
    THREAD_ERR_CHECK(ret,"mutex_init")
    ret=pthread_cond_init(&t.cond,NULL);
    pthread_t pthid;
    ret=pthread_create(&pthid,NULL,func,(void*)&t);//建立子线程
    THREAD_ERR_CHECK(ret,"pthread_create")
    sleep(1);
    ret=pthread_cond_signal(&t.cond);
    THREAD_ERR_CHECK(ret,"pthread_cond_signal")
    pthread_join(pthid,NULL);//等待子线程
    ret=pthread_mutex_destroy(&t.mutex);//销毁锁
    THREAD_ERR_CHECK(ret,"destroy");
    printf("主进程结束\n");
    return 0;
}