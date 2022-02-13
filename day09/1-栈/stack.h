#include <stdio.h>
typedef struct tag
{
	int m_ival;
	struct tag* next;
}Node,*pNode;

typedef struct {
	pNode phead;//栈顶，也是链表头
	int size;
}Stack,*pStack;

void init_stack(pStack stack);
void pop(pStack stack);
void push(pStack stack, int val);
int top(pStack stack);
int empty(pStack stack);
int size(pStack stack);
