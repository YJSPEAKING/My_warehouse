#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
//ʵ��mystrcpy(), mystrcmp(), mystrcat(), mystrlen() ;��ע��mystrcat()mystrcpy()����ֵΪvoid
void mystrcpy(char to[], char from[],int count)//����Ҫô��to[],Ҫô��*to
											   //��from�����count���ַ����Ƶ�to������
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
	mystrcpy(b, a, 4);//��a�������ǰ4���ַ����Ƶ�b������
	printf("after mystrcpy b = %s\n", b);
	printf("mystrcmp = %d\n", mystrcmp(a, b));//��a�����b��������ַ��Ա�
	mystrcat(a, b, 3);//��b�������ǰ3���ַ�ƴ��a�����
	printf("after mystrcat a = %s\n", a);
	printf("mystrlen a = %d\n", mystrlen(a));//ͳ��a�������ַ�����
	return 0;
}