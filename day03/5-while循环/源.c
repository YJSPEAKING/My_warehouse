#include <stdio.h>
//��1�ӵ�100
//�ų����ѭ����ѭ�����������ڴ�ϵ�
int main()
{
	int i = 1, total = 0;
	while (i <= 100)//while������û�зֺ�
	{
		total = total + i;
		i++;//ʹ�ñ��ʽ�����ڼٵĲ���
	}
	printf("total=%d\n", total);
	return 0;
}