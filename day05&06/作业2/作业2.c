#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void replace(char c[])
{
	char* p = c;
	while (*p)
	{
		if (*p != ' ')
		{
			printf("%c", *p);
		}
		else
		{
			printf("%%020");
		}
		p++;
	}
}
int main()
{
	char c[100];
	gets(c);
	replace(c);
	return 0;
}