#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main()
{
	char str[] = "hello world";
	char str[] = "how do you do";
	char* const p = str;//p不可以再指向别的地方
	p[0] = 'H';
	puts(p);
	return 0;
}