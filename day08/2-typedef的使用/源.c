#include <stdio.h>

//typedefĿ��1��ʡȥÿ�˶�Ҫдstruct student���鷳
typedef struct student//�ṹ���в���struct student*��ʱ�����ȥ��student
{
	int num;
	char name[20];
	char sex;
}stu,*pstu;

//typedefĿ��2�����뼴ע��
//typedefĿ��3��ʡȥ�����޸�intΪ�����������͵��鷳
typedef int ELEMTYPE;

//��Ҫ�ñ������ͽṹ����������
//����Ҫ����һ��pstu stu
int main()
{
	stu s = { 101 };
	pstu p;
	ELEMTYPE i;
	p = &s;
	printf("%d %s %c\n", p->num, p->name, p->sex);//û����Ľṹ�岿��Ĭ��Ϊ0
	return 0;
}