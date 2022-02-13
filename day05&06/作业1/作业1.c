#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void sort(char c[])
{
	char* p, * q;
	p = c;
	q = c;
	while (*q)
	{
		if ('0' <= *q && *q <= '9')
		{
			printf("%c", *q);
		}
		q++;
	}
	while (*p)
	{
		if (('a' <= *p && *p <= 'z') || ('A' <= *p && *p <= 'Z'))
		{
			printf("%c", *p);
		}
		p++;
	}
	printf("\n");
}
int main()
{
	char c[100];
	gets(c);
	sort(c);
	return 0;
}