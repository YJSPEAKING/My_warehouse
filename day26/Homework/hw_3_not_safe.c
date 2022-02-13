//编写代码，通过ctime感受线程安全
//不安全
#include<func.h>
void*  func(void* p)
{
    time_t now;
    time(&now);
    char* q=ctime(&now);
    printf("child time1=%s",q);
    sleep(3);
    printf("child time2=%s",q);
}

int main()
{
    pthread_t pthid;
    int ret=pthread_create(&pthid,NULL,func,NULL);
    THREAD_ERR_CHECK(ret,"pthread_create")
    sleep(1);
    time_t now;
    time(&now);
    printf("main time=  %s",ctime(&now));
    pthread_join(pthid,NULL);
    return 0;
}