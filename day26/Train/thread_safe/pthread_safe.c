#include <func.h>

//立马打印当前时间，sleep(3),再次打印p
void* thread_func(void *q)
{
    time_t now;
    time(&now);
    char buf_time[200];
    ctime_r(&now,buf_time);
    printf("child thread  ctime_r=%s",buf_time);
    sleep(3);
    printf("child thread second ctime_r=%s",buf_time);
    pthread_exit(NULL);
}
//主线程创建子线程，1秒后，获取当前时间打印
//ctime 不是线程安全函数,p指向的是静态局部变量
int main()
{
    pthread_t pthid;
    pthread_create(&pthid,NULL,thread_func,NULL);
    sleep(1);
    time_t now;
    time(&now);
    char buf_time[200];
    ctime_r(&now,buf_time);
    printf("main thread ctime_r=%s",buf_time);
    pthread_join(pthid,NULL);
    return 0;
}