#include <func.h>

//秒数转为gmtime的操作
int main()
{
    time_t now;
    time(&now);//距离1970年1月1号的秒数
    printf("%ld\n",now);
    struct tm *p;
    p=gmtime(&now);
    printf("%04d-%02d-%02d %02d:%02d:%02d 今年第几天%d,星期%d\n",p->tm_year+1900,\
    p->tm_mon+1,p->tm_mday,p->tm_hour+8,p->tm_min,p->tm_sec,p->tm_yday,p->tm_wday);
    return 0;
}