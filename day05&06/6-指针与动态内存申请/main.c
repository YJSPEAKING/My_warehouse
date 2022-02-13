#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main()
{
	int n;//使用多少字节空间
	int* p1;//int是p1基类型
	void* p;//p是无类型指针
	scanf("%d", &n);//读取要申请空间大小
	p = (char*)malloc(n);//分配
						 //sizeof(p)=4  指针都是4字节
	strcpy(p, "hello");
	puts(p);
	free(p);//p不能偏移，必须是最初malloc返回的地址
			//在内核里有记录分配的空间大小，不需要传入分配的大小
			//内存泄漏:程序中已动态分配的堆内存未释放，导致程序运行崩溃等结果
			//free返回值为void，因为free只许成功不许失败
			//没法在free函数里改变p
	p = NULL;//不把p变为NULL，p就变成了一个“野指针”
	return 0;
}