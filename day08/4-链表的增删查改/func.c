#include "func.h"
//ͷ�巨
void list_head_insert(LinkList* pphead, LNode** pptail, ElemType i)
{
	LinkList pnew = (LinkList)malloc(sizeof(LNode));//����һ���ṹ���С�ռ�
	pnew->num = i;
	pnew->pnext = NULL;
	//��������ǿգ��½����ͷ���(Ҳ�������һ����㣩
	if (NULL == *pphead)
	{
		*pphead = pnew;//�½����Ϊͷ��㣬Ҳ��Ϊβ���
		*pptail = pnew;
	}
	else {
		pnew->pnext = *pphead;//�½��ָ��ԭ����ͷ��
		*pphead = pnew;
	}
}
//β�巨
void list_tail_insert(LinkList* pphead, LinkList* pptail, ElemType i)
{
	LinkList pnew = (LinkList)malloc(sizeof(LNode));//����һ���ṹ���С�ռ�
	pnew->num = i;
	pnew->pnext = NULL;
	//��������ǿգ��½����ͷ���(Ҳ�������һ����㣩
	if (NULL == *pphead)
	{
		*pphead = pnew;//�½����Ϊͷ��㣬Ҳ��Ϊβ���
		*pptail = pnew;
	}
	else {
		(*pptail)->pnext = pnew;//�½�㸳ֵ��βָ���pnext
		*pptail = pnew;//�½����Ϊ����β
	}
}
//�������
void list_sort_insert(LinkList* pphead, LinkList* pptail, ElemType i)
{
	LinkList pnew = (LinkList)calloc(1, sizeof(LNode));//calloc�������Ŀռ�ȫ����ʼ��Ϊ0
	pnew->num = i;
	LinkList pcur, ppre;
	pcur = ppre = *pphead;//pcur��ppre��ָ������ͷ��
	//��������ǿգ��½����ͷ���(Ҳ�������һ����㣩
	if (NULL == *pphead)
	{
		*pphead = pnew;//�½����Ϊͷ��㣬Ҳ��Ϊβ���
		*pptail = pnew;
	}
	else if (pnew->num < pcur->num)//���뵽ͷ��
	{
		pnew->pnext = pcur;//�½��ָ��ԭ����ͷ��
		*pphead = pnew;
	}
	else {
		while (pcur)//���뵽�м�
		{
			if (pnew->num < pcur->num)
			{
				ppre->pnext = pnew;
				pnew->pnext = pcur;
				return;
			}
			ppre = pcur;
			pcur = pcur->pnext;
		}
		//������뵽�м䣬��return��
		(*pptail)->pnext = pnew;//�½�㸳ֵ��βָ���pnext
		*pptail = pnew;//�½����Ϊ����β
	}
}

//����ɾ��
void list_delete(LinkList* pphead, LinkList* pptail, ElemType i)
{
	LinkList pcur, ppre;
	pcur = ppre = *pphead;//pcur��ppre��ָ������ͷ��
	//���ɾ������ͷ��
	if (i == pcur->num)
	{
		*pphead = pcur->pnext;
		if (NULL == *pphead)
		{
			*pptail = NULL;//���ɾ���������һ����㣬βָ����ΪNULL
		}
		free(pcur);
		pcur = NULL;
	}
	else {//ɾ���м����β��
		while (pcur)
		{
			if (i == pcur->num)//����
			{
				ppre->pnext = pcur->pnext;
				free(pcur);
				break;
			}
			ppre = pcur;
			pcur = pcur->pnext;
		}
		if (NULL == ppre->pnext)//����ɾ������β���
		{
			*pptail = ppre;
		}
		if (NULL == pcur)//���pcurΪNULL������û�ҵ�
		{
			printf("������������\n");
			return;
		}
		pcur = NULL;
	}
}

void list_print(LinkList phead)
{
	while (phead)
	{
		printf("%3d %5.2f\n", phead->num, phead->score);
		phead = phead->pnext;
	}
	putchar('\n');
}

//�����޸�
void list_modify(LinkList phead, ElemType i, float score)
{
	while (phead)
	{
		if (i == phead->num)//�ҵ���Ӧ��ѧ�ţ��޸ĳɼ�
		{
			phead->score = score;
		}
		phead = phead->pnext;
	}

}