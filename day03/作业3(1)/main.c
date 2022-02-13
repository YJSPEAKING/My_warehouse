#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
void change_d_to_b(d)
{
	if (d > 1)
	{
		change_d_to_b(d / 2);
		printf("%d", d % 2);
	}
	else
	{
		printf("%d", d);
		return;
	}
}
int main()
{
	int d;
	scanf("%d", &d);
	change_d_to_b(d);
}