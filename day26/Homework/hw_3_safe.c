//安全
#include <func.h>
void*  func(void* p)
{
    time_t now;
    time(&now);
    char buf[100];//改用局部变量，就不会被影响
    ctime_r(&now,buf);
    printf("child time1=%s",buf);
    sleep(3);
    printf("child time2=%s",buf);
}

int main()
{
    pthread_t pthid;
    int ret=pthread_create(&pthid,NULL,func,NULL);
    THREAD_ERR_CHECK(ret,"pthread_create")
    sleep(1);
    time_t now;
    time(&now);
    char buf[100];
    ctime_r(&now,buf);
    printf("main time=  %s",buf);
    pthread_join(pthid,NULL);
    return 0;
}