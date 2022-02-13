#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
int main()
{
	int d = 0, b, r, i = 0;//b为输入的二进制数，r为每轮的最后一位，i为r所指元素的权重
	scanf("%d", &b);
	while (b != 0)
	{
		r = b % 10;
		b = b / 10;
		d += (r << i);
		i++;
	}
	printf("%d\n", d);//最终输出所转化的十进制d
}