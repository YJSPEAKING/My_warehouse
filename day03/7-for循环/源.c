#include <stdio.h>
//��1�ӵ�100
//�ų����ѭ����ѭ�����������ڴ�ϵ�
int main()
{
	int i, total=0;
	for (i=1; i <= 100;i++)//for�ӷֺŲ�����ѭ��
	{
		if (i % 2 == 0)
		{
			continue;
		}
		total += i;

	}
	printf("total=%d\n", total);
	return 0;
}