#include "queue.h"

int main()
{
	SqQueue Q;
	int ret;//�淵��ֵ
	ElemType ele;//Ԫ��
	//��ʼ��
	initQueue(&Q);
	if (isEmpty(&Q))
	{
		printf("queue is empty\n");
	}
	EnQueue(&Q, 3);
	EnQueue(&Q, 4);
	EnQueue(&Q, 5);
	EnQueue(&Q, 6);
	ret=EnQueue(&Q, 7);
	if (-1 == ret)
	{
		printf("queue is full\n");
	}
	DeQueue(&Q, &ele);
	printf("ele=%d\n", ele);
	return 0;
}