#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
int count = 0;
int i = 0, j = 0;
int m = 0, n = 0;
void path(int m, int n, int i, int j)
{
	if (m < i || n < j)
	{
		if (m < i)
		{
			path(m + 1, n, i, j);
		}
		if (n < i)
		{
			path(m, n + 1, i, j);
		}
	}
	else if (m == i && n == j)
	{
		count++;
	}
}
int main()
{
	printf("����������꣺");
	scanf("%d", &i);
	printf("�����������꣺");
	scanf("%d", &j);
	path(m, n, i, j);
	printf("��%d��·���ߵ�(%d,%d)", count, i, j);
	return 0;
}