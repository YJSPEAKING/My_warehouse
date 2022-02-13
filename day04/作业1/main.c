#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
//实现mystrcpy(), mystrcmp(), mystrcat(), mystrlen() ;备注：mystrcat()mystrcpy()返回值为void
void mystrcpy(char to[], char from[],int count)//这里要么是to[],要么是*to
											   //将from数组的count个字符复制到to数组中
{
	while (count >= 0)
	{
		to[count - 1] = from[count - 1];
		count--;
	}
	return;
}
int mystrcmp(char a[], char b[])
{
	int i = 0;
	while (a[i] && b[i])
	{
		if (a[i] == b[i])
		{
			i++;
		}
		else if (a[i] > b[i])
		{
			return 1;
		}
		else if (a[i] < b[i])
		{
			return -1;
		}
	}
	if (a[i])
	{
		return 1;
	}
	else if (b[i])
	{
		return -1;
	}
}
void mystrcat(char a[], char b[], int count)
{
	int i = 0;
	while (a[i])
	{
		i++;
	}
	a[i + count] = 0;
	while (count > 0)
	{
		a[i + count - 1] = b[count - 1];
		count--;
	}
	return;
}
int mystrlen(char a[])
{
	int i = 0;
	while (a[i])
	{
		i++;
	}
	return i;
}
int main()
{
	char a[10]="hello";
	char b[10]="helo";
	mystrcpy(b, a, 4);//将a数组里的前4个字符复制到b数组中
	printf("after mystrcpy b = %s\n", b);
	printf("mystrcmp = %d\n", mystrcmp(a, b));//将a数组和b数组里的字符对比
	mystrcat(a, b, 3);//将b数组里的前3个字符拼到a数组后
	printf("after mystrcat a = %s\n", a);
	printf("mystrlen a = %d\n", mystrlen(a));//统记a数组里字符个数
	return 0;
}