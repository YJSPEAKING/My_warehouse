#include<func.h>
//没有完成文件类型转换
int main(int argc,char* argv[])
{
    ARGS_CHECK(argc,2);
    DIR* dir;
    dir=opendir(argv[1]);
    ERROR_CHECK(dir,NULL,"opendir");
    struct dirent *p;
    struct stat buf;
    int ret;
    char time_buf[20]={0};
    while((p=readdir(dir)))
    {
        if(!strcmp(p->d_name,".")||!strcmp(p->d_name,".."))//不显示.和..
        {
            continue;
        }
        if(p->d_name[0]=='.')//不显示隐藏文件
        {
            continue;
        }
        memset(time_buf,0,sizeof(time_buf));
        ret=stat(p->d_name,&buf);
        ERROR_CHECK(ret,-1,"stat");
        strcat(time_buf,ctime(&buf.st_mtime)+4);
        time_buf[12]='\0';//将ctime长度限制为12
        printf("mode=%x %2ld %s %s %5ld %s %s\n",\
        buf.st_mode,buf.st_nlink,getpwuid(buf.st_uid)->pw_name,getgrgid(buf.st_uid)->gr_name,buf.st_size,time_buf,p->d_name);
    }
    closedir(dir);
    return 0;
}