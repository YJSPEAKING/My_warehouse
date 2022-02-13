#include "queue.h"
void initQueue(SqQueue* Q)
{
	Q->front = Q->rear = 0;
}
int isEmpty(SqQueue* Q)
{
	return Q->front == Q->rear;
}
//���
int EnQueue(SqQueue* Q, ElemType x)
{
	if ((Q->rear + 1) % MaxSize == Q->front)
	{
		printf("queue is full\n");
		return -1;
	}
	Q->data[Q->rear] = x;//�Ž�ȥ
	Q->rear = (Q->rear + 1) % MaxSize;//Ҫ�����ƣ�������β����Ҫ�ص�ͷ
	return 0;
}
//����
int DeQueue(SqQueue* Q, ElemType* x)
{
	if (isEmpty(Q))
	{
		printf("queue is empty\n");
		return -1;
	}
	*x = Q->data[Q->front];//frontλ�õ���������
	Q->front = (Q->front + 1) % MaxSize;//front������
	return 0;
}