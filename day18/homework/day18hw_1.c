#include<func.h>
//传递一个路径名，深度优先遍历该路径并打印
//重点在于分清path、dir和p
//path是字符串，是路径的全称；  dir是DIR指针；  p是dirent结构体指针，是readdir的输出
int print_path(char *path,int width)//width表示空格数
{
    DIR *dir;
    dir=opendir(path);
    ERROR_CHECK(dir,NULL,"opendir");
    struct dirent *p;//readdir得到的是一个指针
    char buf[1024]={0};
    while((p=readdir(dir)))
    {
        if(!strcmp(p->d_name,".")||!strcmp(p->d_name,".."))
        {
            continue;
        }
        printf("%*s%s\n",width,"",p->d_name);
        if(p->d_type==4)//如果是目录，递归
        {
            memset(buf,0,sizeof(buf));
            sprintf(buf,"%s%s%s",path,"/",p->d_name);
            print_path(buf,width+4);
        }
    }
}
int main(int argc,char* argv[])
{
    ARGS_CHECK(argc,2);
    print_path(argv[1],0);//传参
    return 0;
}