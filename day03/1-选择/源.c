#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main()
{
	int i;
	while (scanf("%d", &i) != EOF)
	{
		if (i > 0)//if后面括号不能加分号，会造成语句体任何时刻都会执行
		{ 
			printf("i is bigger than 0\n");
		}
		else {
			printf("i is not bigger than 0\n");
		}
	}
}