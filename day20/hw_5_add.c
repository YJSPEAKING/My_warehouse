//通过execl拉起来一个add进程，并给其传参3和4，让其求和最终得到7
#include <func.h>
int main(int argc,char* argv[])
{
    ARGS_CHECK(argc,3);
    int a=atoi(argv[1]);
    int b=atoi(argv[2]);
    printf("%d+%d=%d\n",a,b,a+b);
    return 0;
}