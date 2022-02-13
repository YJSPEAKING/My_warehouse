#include <func.h>
//删除普通文件，管道文件，软连接文件
int main(int argc,char* argv[])
{
    ARGS_CHECK(argc,2)
    int ret;
    ret=unlink(argv[1]);
    ERROR_CHECK(ret,-1,"unlink");
    return 0;
}