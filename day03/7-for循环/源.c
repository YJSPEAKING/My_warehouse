#include <stdio.h>
//从1加到100
//排除多层循环死循环，从外往内打断点
int main()
{
	int i, total=0;
	for (i=1; i <= 100;i++)//for加分号不会死循环
	{
		if (i % 2 == 0)
		{
			continue;
		}
		total += i;

	}
	printf("total=%d\n", total);
	return 0;
}