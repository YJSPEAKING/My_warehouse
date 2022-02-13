//完成端口的主机及网络字节序的来回转换
//短整型来回切换
#include<func.h>

int main()
{
    uint16_t num,num2;
    uint16_t i=0x1234;
    printf("%x\n",i);
    num=htons(i);//把i变成网络字节序
    printf("%x\n",num);
    num2=ntohs(num);//把num变成主机字节序
    printf("%x\n",num2);
    return 0;
}