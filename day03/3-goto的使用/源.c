#include <stdio.h>
//从1加到100,goto向上跳转是循环
int main()
{
	int i = 1, total = 0;
label:
	total = total + i;
	i++;
	if (i <= 100) 
	{
		goto label;
	}
	printf("total=%d\n", total);
	return 0;
}