#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
int main()
{
	int a[3] = { 2,7,9 };
	int* p;
	int j;
	p = a;
	j = *p++;//��һ�� j=*p  �ڶ��� p++
			 //++��ô��Ͽ����ȼ�
	printf("a[0]=%d,j=%d,*p=%d\n", a[0], j, *p);//2 2 7

	j = p[0]++;//��һ�� j=p[0]  �ڶ��� p[0]++
			   //p[0]��*p�ȼ�
	printf("a[0]=%d,j=%d,*p=%d\n", a[0], j, *p);//2 7 8

	return 0;
}