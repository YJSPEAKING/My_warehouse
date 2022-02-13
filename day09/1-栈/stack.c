#include "stack.h"
//��ʼ��ջ
void init_stack(pStack stack)
{
	stack->phead = NULL;
	stack->size = 0;
}
void pop(pStack stack)
{
	if (!stack->phead)
	{
		printf("stack is empty\n");
		return;
	}
	//ͷ��ɾ����
	pNode pcur = stack->phead;
	stack->phead = pcur->next;
	free(pcur);
	pcur = NULL;
	stack->size--;
}
void push(pStack stack, int val)
{
	pNode pnew = (pNode)calloc(1, sizeof(Node));
	pnew->m_ival = val;
	//ͷ�巨
	if (NULL == stack->phead)
	{
		stack->phead = pnew;
	}
	else {
		pnew->next = stack->phead;
		stack->phead = pnew;
	}
	stack->size++;
}
//ֻ����ջ��Ԫ�أ�����ջ
int top(pStack stack)
{
	if (!stack->phead)
	{
		printf("stack is empty\n");
		return -1;
	}
	return stack->phead->m_ival;
}
int empty(pStack stack)
{
	if (!stack->phead)
	{
		return 1;
	}
	else {
		return 0;
	}
}
int size(pStack stack){
	return stack->size;
}