#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

void print(int(*a)[4], int row)
{
	int i, j;
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < sizeof(*a) / sizeof(int); j++)
		{
			printf("%3d", a[i][j]);
		}
		printf("\n");
	}
}
//数组指针+1，是偏移一个数组的大小
int main()
{
	int a[3][4] = { 1,3,5,7,9,11,13,15,17,21,23,25 };
	int b[4] = { 1,2,3,4 };
	int i = 10;
	int(*p)[4];//p就是数组指针
	p = a;
	print(a, 4);
	return 0;
}