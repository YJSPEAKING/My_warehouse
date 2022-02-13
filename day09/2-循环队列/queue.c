#include "queue.h"
void initQueue(SqQueue* Q)
{
	Q->front = Q->rear = 0;
}
int isEmpty(SqQueue* Q)
{
	return Q->front == Q->rear;
}
//入队
int EnQueue(SqQueue* Q, ElemType x)
{
	if ((Q->rear + 1) % MaxSize == Q->front)
	{
		printf("queue is full\n");
		return -1;
	}
	Q->data[Q->rear] = x;//放进去
	Q->rear = (Q->rear + 1) % MaxSize;//要往后移，到数组尾部，要回到头
	return 0;
}
//出队
int DeQueue(SqQueue* Q, ElemType* x)
{
	if (isEmpty(Q))
	{
		printf("queue is empty\n");
		return -1;
	}
	*x = Q->data[Q->front];//front位置的数据拿走
	Q->front = (Q->front + 1) % MaxSize;//front往后移
	return 0;
}