#include"func.h"
//func.c��print_star��print_mess��ʵ�֣�Ҳ�ƶ���
int print_star(int i, int j)
{
	printf("*******************\n");
	printf("print_star i = %d\n", i);
	return i + 3;
}
//main��������print_mess������print_mess��������print_star�����������Ƕ�׵���
void print_mess()
{
	printf("how do you do\n");
	print_star(5, 4);
}