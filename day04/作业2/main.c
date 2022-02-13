#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
int wordnum(char c[])
{
	int i = 1, j = 0, num = 0;
	if (c[0] != 32)
	{
		num++;
	}
	while (c[i])
	{
		if (c[i] != 32 && c[j] == 32)
		{
			num++;
		}
		i++;
		j++;
	}
	return num;
}
int main()
{
	char c[100];
	gets(c);
	printf("%d\n", wordnum(c));
	return 0;
}