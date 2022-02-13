#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main()
{
	char* p = "hello";//p指向字符串常量区
	char c[10] = "hello";//等价于strcpy(c,"hello")
	c[0] = 'H';
	//p[0] = 'H';//不可以修改字符串常量区，也不可以strcpy，因为是只读的
	printf("p = %s\n", p);
	printf("c = %s\n", c);
	p = "world";//p可以随便指
	puts(p);
	//c="world";//不可以的，c是const不是变量
	return 0;
}