#define _CRT_SECURE_NO_WARNINGS
#include<math.h>
#include<stdlib.h>
#include<stdio.h>
int main()
{
	char a[32] = { 0 };
	while (rewind(stdin), scanf("%s", &a) != EOF)
	{
		int d = 0, h = 0, i = 0;
		int len = 0, num = 0;
		while (a[num] != '\0')
		{
			num++;
		}
		len = num;
		while (i < len)
		{
			if ('0' <= a[i] && a[i] <= '9')
			{
				d += (a[i] - '0') * pow(16, len - i - 1);
			}
			else
			{
				d += (a[i] - 'A' + 10) * pow(16, len - i - 1);
			}
			i++;
		}
		printf("对应的十进制为%d\n", d);//最终输出所转化的十进制d
		int j = 0;
		while (j < len)
		{
			a[j] = 0;
			j++;
		}
	}
	return 0;
}