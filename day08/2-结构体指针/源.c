#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

struct student
{
	int num;
	char name[20];
	char sex;
};

int main()
{
	struct student s = { 101,"lele",'m' };
	struct student* p;
	struct student sarr[3] = { 1001,"lilei",'M',1005,"zhangsan",'M',1007,"lili",'f' };
	int num;
	p = &s;

	//ͨ���ṹ��ָ��ȥ����ÿһ����Ա
	printf("%d %s %c\n", p->num, p->name, p->sex);
	printf("%d %s %c\n", (*p).num, (*p).name, (*p).sex);//(*p).��p->�ȼۣ��ṹ��ָ�����д->
	p = sarr;
	num = p->num++;//num=p->num;p->num�������++
	printf("num=%d,p->num=%d\n", num, p->num);//1001 1002
	num = p++->num;//num=p->num;p����++
	printf("num=%d,p->num=%d\n", num, p->num);//1001 1005
	return 0;
}