#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void delete(char c[],char a)
{
	char* p = c;
	while (*p)
	{
		if (*p != a)
		{
			printf("%c", *p);
		}
		p++;
	}
}
int main()
{
	char c[100];
	char a=' ';
	printf("×Ö·û´®£º");
	gets(c);
	printf("É¾³ýÖ¸¶¨×Ö·û£º");
	scanf("%c", &a);
	delete(c,a);
	return 0;
}