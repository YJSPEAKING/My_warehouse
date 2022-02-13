#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main()
{
	const int monday = 1;//const常量使用
	//monday = 3;//不可修改
	const char str[] = "helloworld";//const修饰char*时，str指向的内容不能用str指针修改
	char* p;
	p = str;
	//str[0] = 'H';
	puts(str);
	p[1] = "E";
	puts(p);
	return 0;
}