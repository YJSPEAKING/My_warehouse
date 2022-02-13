#include <func.h>
//新建一个文件，里边内容为hello，通过mmap映射该文件后，修改hello为world，然后解除映射
int main(int argc,char* argv[])
{
    ARGS_CHECK(argc,2);
    //第一步：用open创建文件，用write写hello
    int fd;
    fd=open(argv[1],O_RDWR|O_CREAT|O_EXCL,0666);
    ERROR_CHECK(fd,-1,"open")
    //第二步：用write写hello
    write(fd,"hello",5);//此时文件内容为hello
    //第三步：映射该文件
    int ret;
    char *p;
    char buf[]={"world"};
    p=(char*)mmap(NULL,5,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
    ERROR_CHECK(p,(char*)-1,"mmap")
    //第四步：修改hello为world
    for(int i=0;i<5;i++)
    {
        p[i]=buf[i];
    }
    //第五步：解除映射
    ret=munmap(p,5);//解除映射
    ERROR_CHECK(ret,-1,"munmap")
    close(fd);
    return 0;
}