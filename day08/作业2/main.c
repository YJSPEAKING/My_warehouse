#include "func.h"

int main()
{
	LinkList phead = NULL, ptail = NULL;
	int i;
	while (scanf("%d", &i) != EOF)
	{
		//list_head_insert(&phead, &ptail, i);
		//list_tail_insert(&phead, &ptail, i);
		list_sort_insert(&phead, &ptail, i);
	}
	print_list(phead);
	while (printf("������ɾ�����ֵ\n"), scanf("%d", &i) != EOF)
	{
		list_delete(&phead, &ptail, i);
		print_list(phead);
	}
	return 0;
}