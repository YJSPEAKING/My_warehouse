#include "func.h"

int main()
{
	LinkList phead = NULL, ptail = NULL;
	ElemType i;
	while (scanf("%d", &i) != EOF)
	{
		//list_head_insert(&phead, &ptail, i);
		list_tail_insert(&phead, &ptail, i);
		//list_sort_insert(&phead, &ptail, i);
	}
	list_print(phead);
	//while (printf("请输入删除结点值\n"), scanf("%d", &i) != EOF)
	//{
	//	list_delete(&phead, &ptail, i);
	//	list_print(phead);
	//}
	//float f;
	//while (scanf("%d%f", &i, &f) != EOF)
	//{
	//	list_modify(phead, i, f);//输入对应学号，修改它的成绩
	//	list_print(phead);
	//}
	return 0;
}