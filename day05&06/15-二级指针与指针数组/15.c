#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
//����ָ���ʾ����ָ�������ָ�룬ֻ��һ��ָ�����(�������ָ��)
//ָ������һ��Ͷ�ά�������ʹ�ã�������洢����ָ�루������ָ������飩
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
void print(char** p)
{
	int i;
	for (i = 0; i < 5; i++)
	{
		puts(p[i]);
	}
}
int main()
{
	char* p[5];
	char b[5][10] = { "lele","fenghua","java","python","c" };
	int i, j;
	char** p2;
	for (i = 0; i < 5; i++)
	{
		p[i] = b[i];//p[0]���ַ�ָ������
					//b[0]һά�ַ������������
	}
	p2 = p;//&p[0]��������p�ڲ����洢��ָ�������Ƕ���ָ��
	print(p2);
	char* ptmp;
	for (i = 4; i > 0; i--)
	{
		for (j = 0; j < i; j++)
		{
			if (strcmp(p[j], p[j + 1]) > 0)
			{
				ptmp = p[j];
				p[j] = p[j + 1];
				p[j + 1] = ptmp;
			}
		}
	}
	printf("-----------------------------\n");
	print(p2);//������ַ���
	printf("-----------------------------\n");
	return 0;
}