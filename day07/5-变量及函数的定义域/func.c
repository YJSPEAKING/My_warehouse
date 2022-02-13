#include "func.h"
int k;//extern 借用
void print()//static 修饰函数不可以被别的文件调用
{
	static int i = 0;
	i++;
	printf("print 执行了%d\n", i);
	printf("print k=%d\n", k);
}