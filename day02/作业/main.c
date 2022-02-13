#include<stdio.h>
int main()
{
	int k;//表示乘法的结果
	for (int i = 1; i <= 9; i++)
	{
		for (int j = 1; j <= i; j++)
		{
			k = i * j;
			printf("%d*%d=%-2d ", j, i, k);
		}
		printf("\n");
	}
	return 0;
}