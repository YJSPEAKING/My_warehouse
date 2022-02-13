#include"func.h"

void num_sort(Student* p[])
{
	int i, j;
	Student* tmp;
	for (i = 4; i >= 0; i--)
	{
		for (j = 0; j < i; j++)
		{
			if (p[j]->num > p[j + 1]->num)
			{
				tmp = p[j];
				p[j] = p[j + 1];
				p[j + 1] = tmp;
			}
		}
	}
}

void score1_sort(Student* p[])
{
	int i, j;
	Student* tmp;
	for (i = 4; i >= 0; i--)
	{
		for (j = 0; j < i; j++)
		{
			if (p[j]->score1 > p[j + 1]->score1)
			{
				tmp = p[j];
				p[j] = p[j + 1];
				p[j + 1] = tmp;
			}
		}
	}
}

void score2_sort(Student* p[])
{
	int i, j;
	Student* tmp;
	for (i = 4; i >= 0; i--)
	{
		for (j = 0; j < i; j++)
		{
			if (p[j]->score2 > p[j + 1]->score2)
			{
				tmp = p[j];
				p[j] = p[j + 1];
				p[j + 1] = tmp;
			}
		}
	}
}
void score3_sort(Student* p[])
{
	int i, j;
	Student* tmp;
	for (i = 4; i >= 0; i--)
	{
		for (j = 0; j < i; j++)
		{
			if (p[j]->score3 > p[j + 1]->score3)
			{
				tmp = p[j];
				p[j] = p[j + 1];
				p[j + 1] = tmp;
			}
		}
	}
}

float average1(Student sarr[])
{
	int i;
	float ave = 0;
	for (i = 0; i < 5; i++)
	{
		ave += sarr[i].score1;
	}
	ave /= 5;
	return ave;
}
float average2(Student sarr[])
{
	int i;
	float ave = 0;
	for (i = 0; i < 5; i++)
	{
		ave += sarr[i].score2;
	}
	ave /= 5;
	return ave;
}
float average3(Student sarr[])
{
	int i;
	float ave = 0;
	for (i = 0; i < 5; i++)
	{
		ave += sarr[i].score3;
	}
	ave /= 5;
	return ave;
}

void total_sort(Student* p[])
{
	int i, j;
	Student* tmp;
	for (i = 4; i >= 0; i--)
	{
		for (j = 0; j < i; j++)
		{
			if (p[j]->score1 + p[j]->score2 + p[j]->score3 < p[j + 1]->score1 + p[j + 1]->score2 + p[j + 1]->score3)
			{
				tmp = p[j];
				p[j] = p[j + 1];
				p[j + 1] = tmp;
			}
		}
	}
}