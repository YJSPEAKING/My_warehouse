#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
void change(char* d)//改变数组内容
{
	*d = 'H';
	d[1] = 'E';
	*(d + 2) = 'L';
}
int main()
{
	char c[10] = "hello";
	char* p = c;
	change(c);
	puts(c);
	char d = *++p;
	printf("d = %c\n", d);
	return 0;
}