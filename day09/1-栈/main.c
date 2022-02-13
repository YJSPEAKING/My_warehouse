#include "stack.h"

int main()
{
	Stack s;
	init_stack(&s);
	push(&s, 10);
	push(&s, 5);
	printf("stack top val=%d\n", top(&s));
	pop(&s);
	pop(&s);
	printf("stack is empty?%c\n", empty(&s) ? 'Y':'N');
	return 0;
}