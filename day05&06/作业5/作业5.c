#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main()
{
	char c[100];
	gets(c);
	char* p = c, * q = c + 1;//p指向字符，q指向空格
	if (*p == ' ')
	{
		while (*q == ' ')
		{
			q++;
		}
	}
	p = q;
	while (*p && *q)
	{
		if (*p != ' ' && *(p + 1) != ' ')
		{
			printf("%c", *p);
			p++;
		}
		if (*p != ' ' && *(p + 1) == ' ')
		{
			printf("%c", *p);
			q = p + 1;
			while (*q == ' ')
			{
				q++;
			}
			if (*q)
			{
				printf("_");
			}
			p = q;
		}
	}
	return 0;
}