#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
void putwords(char c[])
{
	int i = 0, j = 0;
	int k = 0, l = 0;
	while (c[i])
	{
		if (c[i] != 32)
		{
			printf("%c", c[i]);
			if (c[i + 1] == 32)
			{
				printf("\n");
			}
		}
		i++;
	}
}
int main()
{
	char c[100];
	gets(c);
	putwords(c);
	return 0;
}