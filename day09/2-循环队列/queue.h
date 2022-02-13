#include <stdio.h>

#define MaxSize 5
typedef int ElemType;
typedef struct {
	ElemType data[MaxSize];//数组，循环队列存储MaxSize-1个元素
	int front, rear;//队列头，队列尾下标
}SqQueue;

void initQueue(SqQueue* Q);
int isEmpty(SqQueue* Q);
int EnQueue(SqQueue* Q, ElemType x);
int DeQueue(SqQueue* Q, ElemType* x);
