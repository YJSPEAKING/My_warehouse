#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
//输入一个年份和月份
int main()
{
	int year, mon;
	while (scanf("%d%d", &year, &mon) != EOF)
	{
		switch (mon)
		{
		case 4:
		case 6:
		case 9:
		case 11:printf("mon=%d is 30 days\n", mon); break;//不用break的话后面的case都会执行

		case 2:printf("mon=%d is %d days\n", mon, 28 + (year % 4 == 0 && year % 100 != 0 || year % 400 == 0)); break;
		
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:printf("mon=%d is 31 days\n", mon); break;

		default:
			printf("error month\n");
		}
	}
	return 0;
}