#include <func.h>

#define N 10000000
typedef struct{
    int tickets;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
}data_t;
//窗口1买票
void* sale_windows1(void *p)
{
    int i;
    data_t* d=(data_t*)p;
    while(1)
    {
        pthread_mutex_lock(&d->mutex);
        if(d->tickets>0)//一定要先加锁后去读
        {
            printf("windows1 start sale %d\n",d->tickets);
            d->tickets--;
            if(0==d->tickets)//当票数为零，通知放票
            {
                pthread_cond_signal(&d->cond);
            }
            pthread_mutex_unlock(&d->mutex);
            printf("windows1 finish sale %d\n",d->tickets);
        }else{
            pthread_mutex_unlock(&d->mutex);
            break;
        }
        sleep(1);
    }
}
//窗口2买票
void* sale_windows2(void *p)
{
    int i;
    data_t* d=(data_t*)p;
    while(1)
    {
        pthread_mutex_lock(&d->mutex);
        if(d->tickets>0)
        {
            printf("windows2 start sale %d\n",d->tickets);
            d->tickets--;
            if(0==d->tickets)//当票数为零，通知放票
            {
                pthread_cond_signal(&d->cond);
            }
            pthread_mutex_unlock(&d->mutex);
            printf("windows2 finish sale %d\n",d->tickets);
        }else{
            pthread_mutex_unlock(&d->mutex);
            break;
        }
        sleep(1);
    }
}
//放票线程
void* set_ticket(void* p)
{
    data_t *d=(data_t*)p;
    pthread_mutex_lock(&d->mutex);
    if(d->tickets>0)
    {
        pthread_cond_wait(&d->cond,&d->mutex);//睡觉时，锁就解开了
    }
    d->tickets=10;
    pthread_mutex_unlock(&d->mutex);

}

//两个子线程卖票，加锁的位置
int main()
{
    data_t d;
    d.tickets=20;
    //初试化锁
    int ret=pthread_mutex_init(&d.mutex,NULL);//初始化锁
    THREAD_ERR_CHECK(ret,"pthread_mutex_init");
    //初始化条件变量
    ret=pthread_cond_init(&d.cond,NULL);
    THREAD_ERR_CHECK(ret,"pthread_cond_init");
    pthread_t pthid[3];
    ret=pthread_create(&pthid[2],NULL,set_ticket,(void*)&d);
    THREAD_ERR_CHECK(ret,"pthread_create2");
    ret=pthread_create(&pthid[0],NULL,sale_windows1,(void*)&d);
    THREAD_ERR_CHECK(ret,"pthread_create");
    ret=pthread_create(&pthid[1],NULL,sale_windows2,(void*)&d);
    THREAD_ERR_CHECK(ret,"pthread_create1");

    for(int i=0;i<3;i++)
    {
        pthread_join(pthid[i],NULL);//等待子线程
    }
    printf("main thread tickets=%d\n",d.tickets);
    ret=pthread_mutex_destroy(&d.mutex);//销毁锁
    THREAD_ERR_CHECK(ret,"pthread_mutex_destroy");
    return 0;
}