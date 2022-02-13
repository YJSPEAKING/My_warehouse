#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main()
{
	int c[50] = { 1,2,2,2,3,3,3,4,4,5,5,5,6,6,6 };
	int i = 0, j = 1;
	while (c[i])
	{
		if (c[i] == c[j])
		{
			j++;
		}
		else
		{
			printf("%d ", c[i]);
			i = j;
			j++;
		}
	}
	return 0;
}