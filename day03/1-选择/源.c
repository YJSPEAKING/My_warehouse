#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main()
{
	int i;
	while (scanf("%d", &i) != EOF)
	{
		if (i > 0)//if�������Ų��ܼӷֺţ������������κ�ʱ�̶���ִ��
		{ 
			printf("i is bigger than 0\n");
		}
		else {
			printf("i is not bigger than 0\n");
		}
	}
}