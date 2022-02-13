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

	//通过结构体指针去访问每一个成员
	printf("%d %s %c\n", p->num, p->name, p->sex);
	printf("%d %s %c\n", (*p).num, (*p).name, (*p).sex);//(*p).和p->等价，结构体指针最好写->
	p = sarr;
	num = p->num++;//num=p->num;p->num整体进行++
	printf("num=%d,p->num=%d\n", num, p->num);//1001 1002
	num = p++->num;//num=p->num;p进行++
	printf("num=%d,p->num=%d\n", num, p->num);//1001 1005
	return 0;
}