#include "func.h"
int k;//extern ����
void print()//static ���κ��������Ա�����ļ�����
{
	static int i = 0;
	i++;
	printf("print ִ����%d\n", i);
	printf("print k=%d\n", k);
}