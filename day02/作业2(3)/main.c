#include<stdio.h>
int main()
{
	int i, j, k;//i��ʾ����ţ�j��ʾÿ�еĿո�k��ʾÿ�е�"*"
	for (int i = 2; i <= 14; i++)
	{
		if (i <= 5)//ǰ4��ÿ�и���"*"�Ϳո��Ϊ�ĸ�����
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
		else//��9�з�Ϊ�ո񲿷ֺ�"*"����
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