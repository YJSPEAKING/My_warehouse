#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
//从键盘上输入字符，将小写字母转换成大写字母。输入“ctl + z” 结束 
int main() 
{
	char a;
	while (rewind(stdin), scanf("%c", &a) != EOF)
	{
		if ('a' <= a && a <= 'z')
		{
			printf("%c\n", a - 32);
		}
		else
		{
			printf("%c\n", a);
		}
	}
}