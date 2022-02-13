//编写火车站买票，两个子线程卖票，一个子线程放票（参考课件）
#include<func.h>

struct tickets{
    pthread_mutex_t mutex;
    int num;
    pthread_cond_t cond;
};

void* window1(void *p)
{
    struct tickets *q=(struct tickets*)p;
    while(1)
    {
        pthread_mutex_lock(&q->mutex);
        if(q->num>0)
        {
            printf("一号窗口准备卖票,当前剩余%d\n",q->num);
            q->num--;
            printf("一号成功,当前剩余%d\n",q->num);
            if(q->num==0)
            {
                pthread_cond_signal(&q->cond);//喊放票进程赶紧放票了
            }
            pthread_mutex_unlock(&q->mutex);
        }
        else{
            printf("一号失败,当前剩余%d\n",q->num);
            pthread_mutex_unlock(&q->mutex);
            break;
        }
        usleep(1);
    }
}

void* window2(void *p)
{
    struct tickets *q=(struct tickets*)p;
    while(1)
    {
        pthread_mutex_lock(&q->mutex);
        if(q->num>0)
        {
            printf("二号窗口准备卖票,当前剩余%d\n",q->num);
            q->num--;
            printf("二号成功,当前剩余%d\n",q->num);
            if(0==q->num)
            {
                pthread_cond_signal(&q->cond);//喊放票进程赶紧放票了
            }
            pthread_mutex_unlock(&q->mutex);
        }
        else{
            printf("二号失败,当前剩余%d\n",q->num);
            pthread_mutex_unlock(&q->mutex);
            break;
        }
        usleep(1);
    }
}

void* add_tickets(void *p)
{
    struct tickets *q=(struct tickets*)p;
    pthread_mutex_lock(&q->mutex);
    if(q->num>0)
    {
        pthread_cond_wait(&q->cond,&q->mutex);
    }
    q->num=10;
    printf("补票成功,当前剩余%d\n",q->num);
    pthread_mutex_unlock(&q->mutex);
}

int main()
{
    struct tickets t;
    t.num=10;//初始化票数
    int ret=pthread_mutex_init(&t.mutex,NULL);//初始化锁
    THREAD_ERR_CHECK(ret,"mutex_init")
    ret=pthread_cond_init(&t.cond,NULL);
    THREAD_ERR_CHECK(ret,"cond_init")
    pthread_t pthid[3];
    ret=pthread_create(&pthid[0],NULL,window1,(void*)&t);//建立两个子线程
    THREAD_ERR_CHECK(ret,"pthread_create1")
    ret=pthread_create(&pthid[1],NULL,window2,(void*)&t);
    THREAD_ERR_CHECK(ret,"pthread_create2")
    ret=pthread_create(&pthid[2],NULL,add_tickets,(void*)&t);
    THREAD_ERR_CHECK(ret,"pthread_create3")
    pthread_join(pthid[0],NULL);//等待子线程
    pthread_join(pthid[1],NULL);
    pthread_join(pthid[2],NULL);
    printf("票已售罄，剩余票%d\n",t.num);
    ret=pthread_mutex_destroy(&t.mutex);//销毁锁
    THREAD_ERR_CHECK(ret,"destroy");
    return 0;
}