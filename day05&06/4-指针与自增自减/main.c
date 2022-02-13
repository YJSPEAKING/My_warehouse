#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
int main()
{
	int a[3] = { 2,7,9 };
	int* p;
	int j;
	p = a;
	j = *p++;//第一步 j=*p  第二步 p++
			 //++怎么结合看优先级
	printf("a[0]=%d,j=%d,*p=%d\n", a[0], j, *p);//2 2 7

	j = p[0]++;//第一步 j=p[0]  第二步 p[0]++
			   //p[0]和*p等价
	printf("a[0]=%d,j=%d,*p=%d\n", a[0], j, *p);//2 7 8

	return 0;
}