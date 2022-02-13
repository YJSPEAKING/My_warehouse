#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#define N 5
void print(int* p)//顺序输出
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
	int* p;//指针每次+1，是加sizeof(int)大小
	p = a;
	int i;
	
	print(a);//数组名在传递时弱化为指针
			 //顺序输出数组a
	
	p += 4;//p+=4和p=&p[4]是相同效果
		   //不能使用a+=4，因为a是一个常量const int*，不是一个变量
	putchar('\n');
	printf("p目前指向 = %d\n", *p);
	
	for (i = 0; i < N; i++)//逆序输出
	{
		printf("%3d", *(p - i));
	}
	putchar('\n');
	return 0;
}