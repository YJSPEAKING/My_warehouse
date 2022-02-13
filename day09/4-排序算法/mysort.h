#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 10
#define M 100
#define SWAP(a,b) {int tmp;tmp=a;a=b;b=tmp;}

void bubble(int* a);
void select(int* a);
void insert(int* a);
void shell(int* a);
void quick(int* a,int left,int right);
void heap(int* a);
void merge(int* a, int, int);
void count(int* a);