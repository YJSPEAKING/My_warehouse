#include <func.h>
//popen 以w状态拉起进程，fp是管道的写端
//OJ的测试原理
int main()
{
    FILE *fp;
    fp=popen("./sub","w");
    //可以不需要写\n，因为pclose(fp)的时候自然就会读取
    char buf[1024]="10 5";
    //把10和5写进管道里
    fwrite(buf,1,strlen(buf),fp);
    //关闭管道的时候自然就会读取管道里的数据
    pclose(fp);
    return 0;
}