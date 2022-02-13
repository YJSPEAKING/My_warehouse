#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

int main()
{
	char c[20];
	gets(c);//gets把标准输入缓冲区里的\n读走//gets可以一次读一行
	printf("%s\n", c);
	return 0;
}