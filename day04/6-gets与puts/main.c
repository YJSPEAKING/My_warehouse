#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

int main()
{
	char c[20];
	gets(c);//gets�ѱ�׼���뻺�������\n����//gets����һ�ζ�һ��
	printf("%s\n", c);
	return 0;
}