#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
//数组指针表示的是指向数组的指针，只是一个指针变量(即数组的指针)
//指针数组一般和二维数组搭配使用，数组里存储的是指针（即包含指针的数组）
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
void print(char** p)
{
	int i;
	for (i = 0; i < 5; i++)
	{
		puts(p[i]);
	}
}
int main()
{
	char* p[5];
	char b[5][10] = { "lele","fenghua","java","python","c" };
	int i, j;
	char** p2;
	for (i = 0; i < 5; i++)
	{
		p[i] = b[i];//p[0]是字符指针类型
					//b[0]一维字符数组的数组名
	}
	p2 = p;//&p[0]————p内部所存储的指针类型是二级指针
	print(p2);
	char* ptmp;
	for (i = 4; i > 0; i--)
	{
		for (j = 0; j < i; j++)
		{
			if (strcmp(p[j], p[j + 1]) > 0)
			{
				ptmp = p[j];
				p[j] = p[j + 1];
				p[j + 1] = ptmp;
			}
		}
	}
	printf("-----------------------------\n");
	print(p2);//有序的字符串
	printf("-----------------------------\n");
	return 0;
}