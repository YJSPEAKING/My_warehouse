//完成端口的主机及网络字节序的来回转换
//长整型来回转换
#include<func.h>
int main()
{
    uint32_t num,num2;
    uint32_t i=0x12345678;
    printf("%x\n",i);
    num=htonl(i);//把i变成网络字节序
    printf("%x\n",num);
    num2=ntohl(num);//把num变成主机字节序
    printf("%x\n",num2);
    return 0;
}