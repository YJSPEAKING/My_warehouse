#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
int main()
{
	int d = 0, b, r, i = 0;//bΪ����Ķ���������rΪÿ�ֵ����һλ��iΪr��ָԪ�ص�Ȩ��
	scanf("%d", &b);
	while (b != 0)
	{
		r = b % 10;
		b = b / 10;
		d += (r << i);
		i++;
	}
	printf("%d\n", d);//���������ת����ʮ����d
}