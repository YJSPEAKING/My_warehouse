#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//Ұָ���������Ŀռ䣬�ͷź�û��ָ�븳ֵΪNULL���ͱ��Ұָ��
int main()
{
	int* p1, * p2, * p3;
	p1 = (int*)malloc(4);
	*p1 = 1;
	p2= (int*)malloc(4);//���û��p2��p1�ٸ�ֵ����ȵ�p3��malloc�㷨���ص㣩
	*p2 = 2;
	free(p1);//freeǰ���ܸı�p1��ֵ�������Ըı�*p��ֵ��
	p3= (int*)malloc(4);//p3������ڴ��p1������һ�£����Ի��p1�ͷŵĿռ��p3
	*p3 = 3;
	printf("*p3 = %d\n", *p3);//*p3=3
	*p1 = 100;
	printf("*p3 = %d\n", *p3);//*p3=100
	p1 = NULL;//��������Ұָ��
	return 0;
}