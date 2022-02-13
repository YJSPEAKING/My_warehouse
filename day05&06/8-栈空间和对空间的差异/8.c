#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//函数在调用结束以后，内部的局部变量全部会释放掉
char* print_stack()
{
	char c[17] = "I am print_stack";
	puts(c);
	return c;
}
//堆空间不会因为函数执行结束而释放
char* print_malloc()
{
	char* p;
	p = (char*)malloc(40);
	strcpy(p, "I am print_malloc");
	puts(p);
	return p;//返回指针p
}
int main()
{
	char* p;
	p = print_stack();
	puts(p);
	p = print_malloc();
	puts(p);
	free(p);
	return 0;
}