#include <stdio.h>
int i = 10;//main������ʼ����֮ǰ�͸�ֵ��
		   //ȫ�ֱ��������Ĳ��ֶ���Ч
		   //�����int i��i=10�ֿ�д����i=10�������Ĳ��ֶ���Ч��int i��д�ں���i����ǰ
void print(int a)
{
	printf("print i=%d\n", i);
}
int main()
{
	printf("main i=%d\n", i);
	int i;
	i = 5;
	print(i);
	return 0;
}