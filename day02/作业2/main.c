#include<stdio.h>
int main()
{
	int i, j, k;//i,j,k�ֱ��ʾ����š�ÿ��ǰ����Ҫ�յĸ�����ÿ����Ҫ��ӡ��"*"��
	for (i = 1; i <= 9; i++)
	{
		for (j = (i <= 5) ? (5 - i) : (i - 5); j >= 0; j--)
		{
			printf(" ");
		}
		for (k = (i <= 5) ? i : (10 - i); k > 0; k--)
		{
			printf("* ");
		}
		printf("\n");
	}
	return 0;
}