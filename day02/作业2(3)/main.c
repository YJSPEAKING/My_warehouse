#include<stdio.h>
int main()
{
	int i, j, k;//i表示行序号，j表示每行的空格，k表示每行的"*"
	for (int i = 2; i <= 14; i++)
	{
		if (i <= 5)//前4行每行根据"*"和空格分为四个部分
		{
			for (j = 5 - i; j > 0; j--)
				printf(" ");
			for (k = 1; k <= i; k++)
				printf("* ");
			for (j = 5 - i; j > 0; j--)
				printf("  ");
			for (k = 1; k <= i; k++)
				printf("* ");
			printf("\n");
		}
		else//后9行分为空格部分和"*"部分
		{
			for (j = i - 5; j > 0; j--)
				printf(" ");
			for (k = (15 - i); k > 0; k--)
				printf("* ");
			printf("\n");
		}
	}
	return 0;
}