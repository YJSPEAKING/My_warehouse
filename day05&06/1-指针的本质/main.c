#include<stdio.h>
//scanf("%d",&i)��printf("%d",i)����ֱ�ӷ���
//ָ��ı����Ǽ�ӷ���
int main()
{
	int i = 10;
	int* p = &i;//CPU��ָ�����ͽ�����ָ���ݣ���iֻ����int����
	//&*p==p,*&i==i
	printf("i=%d\n", i);//ֱ�ӷ���
	printf("*p=%d\n", *p);//��ӷ���
	return 0;
}