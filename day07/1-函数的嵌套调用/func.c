#include"func.h"
//func.c是print_star和print_mess的实现，也称定义
int print_star(int i, int j)
{
	printf("*******************\n");
	printf("print_star i = %d\n", i);
	return i + 3;
}
//main函数调用print_mess函数，print_mess函数调用print_star函数，这就是嵌套调用
void print_mess()
{
	printf("how do you do\n");
	print_star(5, 4);
}