#include<stdio.h>
//��ͬ�������������໥������ջ�ռ䣨����ջ��
void change1(int j)
{
	j = 5;
}
//C�����βε�λ�ò��ܳ���&����ΪC���Բ�֧������
void change2(int *j)//j���β�
					//j=&i
{
	*j = 5;
}
//ָ��Ĵ���ʹ�ó���
int main()
{
	int i = 10;
	printf("before change i=%d\n", i);
	change1(i);//��change1��i��Ϊ5����change��i�ͱ��10
	change2(&i);//i����ʵ�Σ�ʵ�θ�ֵ���βεĹ��̣�ֻ�ܸ�ֵ�����ܸ����ͣ�
	printf("after change i=%d\n", i);
	return 0;
}