#include <stdio.h>
//��1�ӵ�100
//�ų����ѭ����ѭ�����������ڴ�ϵ�
int main()
{
	int i = 1, total = 0;
	do {
		total += i;
		i++;
	} while (i<=100);
	printf("total=%d\n", total);
	return 0;
}