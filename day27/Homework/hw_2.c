//完成点分十进制转换为网络字节序
#include<func.h>

int main()
{
    char *ip="192.168.3.1";
    in_addr_t n;
    struct in_addr addr;
    int ret=inet_aton(ip,&addr);
    if(ret==0)
    {
        printf("aton_error\n");
    }
    printf("%x\n",addr.s_addr);
    printf("-----------\n");
    char buf[20];
    strcpy(buf,inet_ntoa(addr));
    printf("%d\n",ret);
    printf("%s\n",buf);
    return 0;
}