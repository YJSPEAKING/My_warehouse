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
			if (pnew->data < (*pphead)->data)//���ڿ�ͷ�����
			{
				pnew->next = *pphead;
				*pphead = pnew;
				return;
			}
			else if (pcur->data > pnew->data)//�����м�
			{
				ppre->next = pnew;
				pnew->next = pcur;
				return;
			}
			ppre = pcur;
			pcur = pcur->next;
		}
		ppre->next = pnew;//���ߵ��⣬˵��Ҫ�������
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
		printf("ɾ��ʧ�ܣ�������\n");
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
				if (pcur == *pptail)//ɾ��β�������
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
	printf("ɾ��ʧ�ܣ��������롣\n");
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