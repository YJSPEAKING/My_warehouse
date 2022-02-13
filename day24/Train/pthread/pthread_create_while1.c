#include <func.h>

//线程函数,pthread_func执行结束，线程就结束了
void* pthread_func(void *p)
{
    printf("I am child thread\n");
    while(1);
}
//pthread开头的函数都不可以用perror来定位错误
int main()
{
    pthread_t pthid;//先定义一个线程id
    int ret=pthread_create(&pthid,NULL,pthread_func,NULL);//第四个参数是给线程函数传递的参数
    if(ret!=0)
    {
        printf("pthread_create failed\n");
        return -1;
    }
    usleep(1);//睡一下，否则子线程没有创建成功，主线程就关闭了标准输出
    printf("I am main thread\n");
    while(1);
    return 0;
}