#include <stdio.h>
//��1�ӵ�100,goto������ת��ѭ��
int main()
{
	int i = 1, total = 0;
label:
	total = total + i;
	i++;
	if (i <= 100) 
	{
		goto label;
	}
	printf("total=%d\n", total);
	return 0;
}