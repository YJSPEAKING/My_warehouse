#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
void change_d_to_h(d)
{
	if (d > 15)
	{
		change_d_to_h(d / 16);
		if (d % 16 < 10)
		{
			printf("%d", d % 16);
		}
		else
		{
			switch (d % 16)
			{
			case 10:printf("A"); break;
			case 11:printf("B"); break;
			case 12:printf("C"); break;
			case 13:printf("D"); break;
			case 14:printf("E"); break;
			case 15:printf("F"); break;
			}
		}
	}
	else
	{
		if (d < 10)
		{
			printf("%d", d % 16);
		}
		else
		{
			switch (d)
			{
			case 10:printf("A"); break;
			case 11:printf("B"); break;
			case 12:printf("C"); break;
			case 13:printf("D"); break;
			case 14:printf("E"); break;
			case 15:printf("F"); break;
			}
		}
	return;
	}
}
int main()
{
	int d;
	scanf("%d", &d);
	change_d_to_h(d);
}