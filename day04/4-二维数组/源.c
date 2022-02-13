#include <stdio.h>
void print_arr(int a[][4], int row)
{
	int i, j;
	for (j = 0; j < sizeof(a[0]) / sizeof(int); j++)
	{
		printf("%3d", a[i][j]);
	}
	printf("\n");//每完成一行的打印，打一个换行
}


int main()
{
	int a[3][4] = { 1,3,5,7,2,4,6,8,11,13,15,17 };
	int b[4] = { 1,2,3,4 };
	//int a[3][4] = { {1},{0,5},{9} };//此方式可表示每行的元素
	print_arr(a, 3);
	printf("a[1][2]=%d\n", a[1][2]);
	return 0;
}