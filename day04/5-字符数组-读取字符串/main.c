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


//�������ڴ�����������ʼ��ַ
//%s����ַ�������һֱ�ң�ֱ������������'\0'
//scanf %s��ȡ�ַ���ʱ���Կո��\n
int main()
{
	char b[6] = "hello";
	char c[6];
	char d[10];
	scanf("%s%s", c, d);//�ӱ�׼�����ȡһ���ַ������ַ�������
	printf("%s---%s\n", c, d);//%s���ʱ��������Ҫ������һ���ַ�������ʼ��ַ
	print_str(c);
	return 0;
}