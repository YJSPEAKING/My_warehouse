#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
//�Ӽ����������ַ�����Сд��ĸת���ɴ�д��ĸ�����롰ctl + z�� ���� 
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