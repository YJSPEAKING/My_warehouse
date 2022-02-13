#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

typedef struct Student {
	int num;
	char name[10];
	int score1;
	int score2;
	int score3;
}Student;

void num_sort(Student* p[]);
void score1_sort(Student* p[]);
void score2_sort(Student* p[]);
void score3_sort(Student* p[]);
float average1(Student sarr[]);
float average2(Student sarr[]);
float average3(Student sarr[]);
void total_sort(Student* p[]);