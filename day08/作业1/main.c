#include"func.h"

int main()
{
	int i, top1, top2, top3;
	Student sarr[5] = { 0 };
	Student* p[5];
	for (i = 0; i < 5; i++)
	{
		p[i] = &sarr[i];
	}
	for (i = 0; i < 5; i++)
	{
		scanf("%d%s%d%d%d", &sarr[i].num, sarr[i].name, &sarr[i].score1, &sarr[i].score2, &sarr[i].score3);
	}

	num_sort(&p);
	printf("��ѧ���������£�\n");
	for (i = 0; i < 5; i++)
	{
		printf("%d %-10s %3d %3d %3d  %3d\n", p[i]->num, p[i]->name, p[i]->score1, p[i]->score2, p[i]->score3, p[i]->score1 + p[i]->score2 + p[i]->score3);
	}

	score1_sort(&p);
	printf("��һ�ſγ̵���߷�ͬѧ��ϢΪ��%d %-10s %3d %3d %3d %3d\n", p[4]->num, p[4]->name, p[4]->score1, p[4]->score2, p[4]->score3, p[4]->score1 + p[4]->score2 + p[4]->score3);
	score2_sort(&p);
	printf("�ڶ��ſγ̵���߷�ͬѧ��ϢΪ��%d %-10s %3d %3d %3d %3d\n", p[4]->num, p[4]->name, p[4]->score1, p[4]->score2, p[4]->score3, p[4]->score1 + p[4]->score2 + p[4]->score3);
	score3_sort(&p);
	printf("�����ſγ̵���߷�ͬѧ��ϢΪ��%d %-10s %3d %3d %3d %3d\n", p[4]->num, p[4]->name, p[4]->score1, p[4]->score2, p[4]->score3, p[4]->score1 + p[4]->score2 + p[4]->score3);

	printf("��һ�ſ�ƽ����Ϊ��%.1f\n", average1(sarr));
	printf("�ڶ��ſ�ƽ����Ϊ��%.1f\n", average2(sarr));
	printf("�����ſ�ƽ����Ϊ��%.1f\n", average3(sarr));

	total_sort(&p);
	printf("�������£�\n");
	for (i = 0; i < 5; i++)
	{
		printf("��%d���� %-10s\n", i + 1, p[i]->name);
	}

	return 0;
}