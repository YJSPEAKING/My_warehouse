#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

//递归调用深度过大，会出现stack overflow
int f(int n)
{
	if (1 == n) //结束条件
	{
		return 1;
	}
	return n * f(n - 1);
}

int step(int n)
{
	if (1 == n || 2 == n)
	{
		return n;
	}
	return step(n - 1) + step(n - 2);
}

int for_step(int n)
{
	int first = 0;
	int second = 1;
	int third = 0;
	int i;
	for (i = 0; i < n; i++)
	{
		third = first + second;
		first = second;
		second = third;
	}
	return third;
}

int main()
{
	int n;
	while (scanf("%d", &n) != EOF)
	{
		//printf("f(%d)=%d\n", n, f(n));
		printf("step(%d)=%d\n", n, for_step(n));
	}
	return 0;
}