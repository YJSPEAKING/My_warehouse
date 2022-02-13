#include <func.h>

int main(int argc,char** argv)
{
    ARGS_CHECK(argc,2);
    struct hostent *p;
    p=gethostbyname(argv[1]);
    if(NULL==p)
    {
        printf("gethostbyname failed\n");
        return -1;
    }
    printf("name=%s\n",p->h_name);//打印真实的域名
    int i;
    for(i=0;p->h_aliases[i]!=NULL;i++)//打印别名
    {
        printf("%s\n",p->h_aliases[i]);
    }
    printf("addrtype=%d\n",p->h_addrtype);//打印地址类型
    printf("addrlen=%d\n",p->h_length);//打印地址长度
    char dst[100];
    for(i=0;p->h_addr_list[i]!=NULL;i++)
    {
        //打印地址，因为地址存储的是网络字节序，所以呢要转换为主机字节序
        bzero(dst,sizeof(dst));
        inet_ntop(p->h_addrtype,p->h_addr_list[i],dst,sizeof(dst));
        puts(dst);
    }
    return 0;
}