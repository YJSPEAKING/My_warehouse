#include<stdio.h>
int main()
{
	int i, j, k;//i,j,k分别表示行序号、每行前面需要空的格数、每行两个"*"之间需要空的格数
	for (i = 1; i <= 9; i++)
	{
		for (j = (i <= 5) ? (5 - i) : (i - 5); j >= 0; j--)
		{
			printf(" ");
		}
		printf("* ");
		for (k = (i <= 5) ? i - 1 : (9 - i); k > 1; k--)
		{
			printf("  ");
		}
		if (i != 1 && i != 9)
			printf("*");
		printf("\n");
	}
	return 0;
}