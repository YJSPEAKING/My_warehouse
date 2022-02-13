#include<stdio.h>
//scanf("%d",&i)和printf("%d",i)都是直接访问
//指针的本质是间接访问
int main()
{
	int i = 10;
	int* p = &i;//CPU以指针类型解析所指内容，即i只能是int类型
	//&*p==p,*&i==i
	printf("i=%d\n", i);//直接访问
	printf("*p=%d\n", *p);//间接访问
	return 0;
}