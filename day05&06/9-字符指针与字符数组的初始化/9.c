#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main()
{
	char* p = "hello";//pָ���ַ���������
	char c[10] = "hello";//�ȼ���strcpy(c,"hello")
	c[0] = 'H';
	//p[0] = 'H';//�������޸��ַ�����������Ҳ������strcpy����Ϊ��ֻ����
	printf("p = %s\n", p);
	printf("c = %s\n", c);
	p = "world";//p�������ָ
	puts(p);
	//c="world";//�����Եģ�c��const���Ǳ���
	return 0;
}