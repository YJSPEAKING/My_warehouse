#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//�����ڵ��ý����Ժ��ڲ��ľֲ�����ȫ�����ͷŵ�
char* print_stack()
{
	char c[17] = "I am print_stack";
	puts(c);
	return c;
}
//�ѿռ䲻����Ϊ����ִ�н������ͷ�
char* print_malloc()
{
	char* p;
	p = (char*)malloc(40);
	strcpy(p, "I am print_malloc");
	puts(p);
	return p;//����ָ��p
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