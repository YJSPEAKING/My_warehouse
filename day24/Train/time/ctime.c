#include <func.h>

int main()
{
    time_t now;
    time(&now);//距离1970年1月1号的秒数
    printf("%ld\n",now);
    printf("字符串时间=%s",ctime(&now));
    return 0;
}