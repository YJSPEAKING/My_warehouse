#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//野指针就是申请的空间，释放后，没有指针赋值为NULL，就变成野指针
int main()
{
	int* p1, * p2, * p3;
	p1 = (int*)malloc(4);
	*p1 = 1;
	p2= (int*)malloc(4);//如果没有p2，p1再赋值不会踩到p3（malloc算法的特点）
	*p2 = 2;
	free(p1);//free前不能改变p1的值（但可以改变*p的值）
	p3= (int*)malloc(4);//p3分配的内存和p1的正好一致，所以会把p1释放的空间给p3
	*p3 = 3;
	printf("*p3 = %d\n", *p3);//*p3=3
	*p1 = 100;
	printf("*p3 = %d\n", *p3);//*p3=100
	p1 = NULL;//即可消除野指针
	return 0;
}