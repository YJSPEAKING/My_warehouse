#include <stdio.h>
int i = 10;//main函数开始运行之前就赋值了
		   //全局变量对其后的部分都生效
		   //如果是int i和i=10分开写，则i=10对于其后的部分都有效，int i须写在含有i函数前
void print(int a)
{
	printf("print i=%d\n", i);
}
int main()
{
	printf("main i=%d\n", i);
	int i;
	i = 5;
	print(i);
	return 0;
}