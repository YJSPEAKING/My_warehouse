#include <func.h>

int global=10;
void* pthread_func(void *p)
{
    global=5;
    printf("I am child thread,%d\n",global);
}

//全局变量，主线程和子线程是不是都可以访问
int main()
{
    pthread_t pthid;
    int ret=pthread_create(&pthid,NULL,pthread_func,NULL);
    if(ret!=0)
    {
        printf("pthread_create failed %s\n",strerror(ret));
        return -1;
    }
    sleep(1);
    printf("I am main thread,global=%d\n",global);
    return 0;
}