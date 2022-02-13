#include <stdio.h>
//从1加到100
//排除多层循环死循环，从外往内打断点
int main()
{
	int i = 1, total = 0;
	do {
		total += i;
		i++;
	} while (i<=100);
	printf("total=%d\n", total);
	return 0;
}