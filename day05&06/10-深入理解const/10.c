#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main()
{
	const int monday = 1;//const����ʹ��
	//monday = 3;//�����޸�
	const char str[] = "helloworld";//const����char*ʱ��strָ������ݲ�����strָ���޸�
	char* p;
	p = str;
	//str[0] = 'H';
	puts(str);
	p[1] = "E";
	puts(p);
	return 0;
}