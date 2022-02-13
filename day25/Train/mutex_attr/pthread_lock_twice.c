#include <func.h>
//同一个线程对一把锁加锁两次会造成死锁
int main()
{
    pthread_mutex_t mutex;
    int ret=pthread_mutex_init(&mutex,NULL);//锁初始化
    THREAD_ERR_CHECK(ret,"pthread_mutex_init");
    pthread_mutex_lock(&mutex);
    printf("lock once success\n");
    pthread_mutex_lock(&mutex);
    printf("lock twice success\n");
    return 0;
}