#include<stdio.h>
int main()
{
	int i, j, k;//i,j,k�ֱ��ʾ����š�ÿ��ǰ����Ҫ�յĸ�����ÿ������"*"֮����Ҫ�յĸ���
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