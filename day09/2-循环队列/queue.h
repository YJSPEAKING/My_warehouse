#include <stdio.h>

#define MaxSize 5
typedef int ElemType;
typedef struct {
	ElemType data[MaxSize];//���飬ѭ�����д洢MaxSize-1��Ԫ��
	int front, rear;//����ͷ������β�±�
}SqQueue;

void initQueue(SqQueue* Q);
int isEmpty(SqQueue* Q);
int EnQueue(SqQueue* Q, ElemType x);
int DeQueue(SqQueue* Q, ElemType* x);
