#include <func.h>
//同一个线程对一把锁加锁两次会造成死锁
int main()
{
    pthread_mutexattr_t mutex_attr;//定义一个锁属性
    pthread_mutexattr_init(&mutex_attr);//初始化锁属性
    pthread_mutexattr_settype(&mutex_attr,PTHREAD_MUTEX_RECURSIVE);//设置为嵌套锁
    pthread_mutex_t mutex;
    int ret=pthread_mutex_init(&mutex,&mutex_attr);//锁初始化，第二个参数是锁属性
    THREAD_ERR_CHECK(ret,"pthread_mutex_init");
    pthread_mutex_lock(&mutex);
    printf("lock once success\n");
    pthread_mutex_lock(&mutex);
    printf("lock twice success\n");
    return 0;
}