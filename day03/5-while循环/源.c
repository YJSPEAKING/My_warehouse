#include <stdio.h>
//从1加到100
//排除多层循环死循环，从外往内打断点
int main()
{
	int i = 1, total = 0;
	while (i <= 100)//while后面有没有分号
	{
		total = total + i;
		i++;//使得表达式趋近于假的操作
	}
	printf("total=%d\n", total);
	return 0;
}