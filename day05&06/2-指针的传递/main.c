#include<stdio.h>
//不同函数，各自有相互独立的栈空间（函数栈）
void change1(int j)
{
	j = 5;
}
//C语言形参的位置不能出现&，因为C语言不支持引用
void change2(int *j)//j叫形参
					//j=&i
{
	*j = 5;
}
//指针的传递使用场景
int main()
{
	int i = 10;
	printf("before change i=%d\n", i);
	change1(i);//出change1里i变为5；出change后i就变回10
	change2(&i);//i叫做实参（实参赋值给形参的过程，只能赋值，不能赋类型）
	printf("after change i=%d\n", i);
	return 0;
}