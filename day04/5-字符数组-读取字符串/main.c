#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

void print_str(char c[])
{
	int i = 0;
	while (c[i])
	{
		pirntf("%c", c[i]);
		i++;
	}
	printf("\n");
}


//数组名内存的是数组的起始地址
//%s输出字符串，会一直找，直到遇到结束符'\0'
//scanf %s读取字符串时忽略空格和\n
int main()
{
	char b[6] = "hello";
	char c[6];
	char d[10];
	scanf("%s%s", c, d);//从标准输入读取一个字符传到字符数组中
	printf("%s---%s\n", c, d);//%s输出时，后面需要给的是一个字符串的起始地址
	print_str(c);
	return 0;
}