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
	printf("请输入横坐标：");
	scanf("%d", &i);
	printf("请输入纵坐标：");
	scanf("%d", &j);
	path(m, n, i, j);
	printf("有%d种路径走到(%d,%d)", count, i, j);
	return 0;
}