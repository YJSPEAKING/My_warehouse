#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

struct student
{
	int num;
	char name[20];
	char sex;
	int age;
	float score;
	char addr[30];
};

int main()
{
	struct student s1 = {1001,"xiongda",'m',5,92.3,"ShenZhen"};
	struct student sarr[3];
	int i = 0;
	//����ͨ����Ա����ȥ����ÿһ����Ա���
	printf("%d %s %c %d %f %s\n", s1.num,s1.name,s1.sex,s1.age,s1.score,s1.addr);
	for (i = 0; i < 3; i++)
	{
		//%d��%s��%f������Կո񣬵���%c������Կո�����%cǰ����Ͽո��������ʱ��Ϳ�����ÿ����Ϣ�м���Ͽո�
		scanf("%d%s %c%d%f%s", &sarr[i].num, sarr[i].name, &sarr[i].sex, &sarr[i].age, &sarr[i].score, sarr[i].addr);
	}
	for (i = 0; i < 3; i++)
	{
		printf("%d %s %c %d %5.2f %s\n", sarr[i].num, sarr[i].name, sarr[i].sex, sarr[i].age, sarr[i].score, sarr[i].addr);
	}
	return 0;
}