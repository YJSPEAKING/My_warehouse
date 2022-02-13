#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
int main()
{
	char c[100] = { 0 };
	strncpy(c, "helloworld", 5);
	puts(c);//输出"hello"
	memset(c, 0, sizeof(c));//内存设置接口//memset函数可以用于将一段内存初始化为某个值
	strncpy(c, "howareyou", 3);//copy3个字符到c里
	puts(c);//字符串长度大于3的部分用\0替换//输出"how"
	printf("strncmp=%d\n", strncmp("xiongda", "xionger", 5));//输出"strncmp=0"
	//比较两个字符串前5个字符大小，等于返回0，小于返回-1，大于返回1
	strncat(c, "do you do,lily", 9);//添加9个字符到c里,并添加结束符
	puts(c);//输出"howdo you do"
	return 0;
}