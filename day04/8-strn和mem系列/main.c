#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
int main()
{
	char c[100] = { 0 };
	strncpy(c, "helloworld", 5);
	puts(c);//���"hello"
	memset(c, 0, sizeof(c));//�ڴ����ýӿ�//memset�����������ڽ�һ���ڴ��ʼ��Ϊĳ��ֵ
	strncpy(c, "howareyou", 3);//copy3���ַ���c��
	puts(c);//�ַ������ȴ���3�Ĳ�����\0�滻//���"how"
	printf("strncmp=%d\n", strncmp("xiongda", "xionger", 5));//���"strncmp=0"
	//�Ƚ������ַ���ǰ5���ַ���С�����ڷ���0��С�ڷ���-1�����ڷ���1
	strncat(c, "do you do,lily", 9);//���9���ַ���c��,����ӽ�����
	puts(c);//���"howdo you do"
	return 0;
}