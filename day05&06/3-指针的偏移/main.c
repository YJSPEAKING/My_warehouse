#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#define N 5
void print(int* p)//˳�����
{
	int i;
	for (i = 0; i < N; i++)
	{
		printf("%3d", *(p + i));
	}
}

int main()
{
	int a[N] = { 1,3,5,7,9 };
	int* p;//ָ��ÿ��+1���Ǽ�sizeof(int)��С
	p = a;
	int i;
	
	print(a);//�������ڴ���ʱ����Ϊָ��
			 //˳���������a
	
	p += 4;//p+=4��p=&p[4]����ͬЧ��
		   //����ʹ��a+=4����Ϊa��һ������const int*������һ������
	putchar('\n');
	printf("pĿǰָ�� = %d\n", *p);
	
	for (i = 0; i < N; i++)//�������
	{
		printf("%3d", *(p - i));
	}
	putchar('\n');
	return 0;
}