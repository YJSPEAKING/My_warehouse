#include"func.h"

void list_head_insert(LinkList* pphead, LinkList* pptail, int n)
{
	LNode* pnew = (LinkList)malloc(sizeof(LNode));
	pnew->data = n;
	if (NULL == *pphead)
	{
		*pphead = pnew;
		*pptail = pnew;
		(*pphead)->next = NULL;
	}
	else
	{
		pnew->next = *pphead;
		*pphead = pnew;
	}
}

void list_tail_insert(LinkList* pphead, LinkList* pptail, int n)
{
	LNode* pnew = (LinkList)malloc(sizeof(LNode));
	pnew->data = n;
	if (NULL == *pphead)
	{
		*pphead = pnew;
		*pptail = pnew;
		(*pphead)->next = NULL;
	}
	else
	{
		(*pptail)->next = pnew;
		*pptail = pnew;
		pnew->next = NULL;
	}
}

void list_sort_insert(LinkList* pphead, LinkList* pptail, int n)
{
	LNode* pnew = (LinkList)malloc(sizeof(LNode));
	LNode* pcur, * ppre;
	pcur = ppre = *pphead;
	pnew->data = n;
	if (NULL == *pphead)
	{
		*pphead = pnew;
		*pptail = pnew;
		(*pphead)->next = NULL;
	}
	else
	{
		while (pcur)
		{
			if (pnew->data < (*pphead)->data)//插在开头的情况
			{
				pnew->next = *pphead;
				*pphead = pnew;
				return;
			}
			else if (pcur->data > pnew->data)//插在中间
			{
				ppre->next = pnew;
				pnew->next = pcur;
				return;
			}
			ppre = pcur;
			pcur = pcur->next;
		}
		ppre->next = pnew;//能走到这，说明要插在最后
		*pptail = pnew;
		pnew->next = NULL;
	}
}

void list_delete(LinkList* pphead, LinkList* pptail, int n)
{
	LNode* pcur, * ppre;
	pcur = ppre = *pphead;
	if (*pphead == NULL && *pptail == NULL)
	{
		printf("删除失败，空链表。\n");
		return;
	}
	if (*pphead == *pptail && (*pphead)->data == n)
	{
		free(*pphead);
		*pphead = *pptail = NULL;
		return;
	}
	if ((*pphead)->data == n)
	{
		*pphead = pcur->next;
		free(pcur);
		return;
	}
	else
	{
		while (pcur)
		{
			if (n == pcur->data)
			{
				if (pcur == *pptail)//删除尾部的情况
				{
					*pptail = ppre;
					ppre->next = NULL;
					free(pcur);
					return;
				}
				ppre->next = pcur->next;
				free(pcur);
				return;
			}
			ppre = pcur;
			pcur = pcur->next;
		}
	}
	printf("删除失败，请检查输入。\n");
}

void print_list(LinkList phead)
{
	while (phead)
	{
		printf("%3d", phead->data);
		phead = phead->next;
	}
	printf("\n");
}