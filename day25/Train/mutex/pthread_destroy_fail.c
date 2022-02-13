#include <func.h>

int main()
{
    pthread_mutex_t mutex;
    int ret=pthread_mutex_init(&mutex,NULL);//锁初始化
    THREAD_ERR_CHECK(ret,"pthread_mutex_init");
    pthread_mutex_lock(&mutex);
    ret=pthread_mutex_destroy(&mutex);//销毁锁时，锁还是锁定状态时，
    THREAD_ERR_CHECK(ret,"pthread_mutex_destroy");
    return 0;
}