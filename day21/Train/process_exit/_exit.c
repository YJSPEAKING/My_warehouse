#include <func.h>

//_exit从子函数让进程结束
int print()
{
    printf("I am print func");
    fflush(stdout);//主动刷新标准输出，刷新就是把缓存区的内容推到屏幕显示
    _exit(3);
    return 0;
}
int main()
{
    print();
    printf("I am main func\n");
    return 0;
}