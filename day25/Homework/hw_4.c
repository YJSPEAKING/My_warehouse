//子线程，主线程，同时对一个变量加2千万，通过加锁，实现最终效果是4千万。
#include<func.h>
#define N 20000000

struct Node{
    pthread_mutex_t mutex;
    long num;
};

void* func(void*p)
{
    struct Node *q=(struct Node*)p;
    //子线程对num++
    for(int i=0;i<N;i++)
    {
        pthread_mutex_lock(&(*q).mutex);
        (*q).num++;
        pthread_mutex_unlock(&(*q).mutex);
    }
    return NULL;
}

int main()
{
    struct Node money;
    money.num=0;
    int ret=pthread_mutex_init(&money.mutex,NULL);
    THREAD_ERR_CHECK(ret,"mutex_init")
    pthread_t pthid;
    ret=pthread_create(&pthid,NULL,func,(void*)&money);
    THREAD_ERR_CHECK(ret,"create")
    //主线程对num++
    for(int i=0;i<N;i++)
    {
        pthread_mutex_lock(&money.mutex);
        money.num++;
        pthread_mutex_unlock(&money.mutex);
    }
    ret=pthread_join(pthid,NULL);
    THREAD_ERR_CHECK(ret,"join")
    ret=pthread_mutex_destroy(&money.mutex);
    THREAD_ERR_CHECK(ret,"mutex_destory")
    printf("num=%ld\n",money.num);
    return 0;
}