#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
typedef int ElemType;
//当结构体自身中出现对应类型指针，不能省略student
typedef struct student
{
	ElemType num;
	float score;
	struct student* pnext;
}LNode, * LinkList;

void list_head_insert(LinkList* pphead, LNode** pptail, ElemType i);
void list_print(LinkList phead);
void list_tail_insert(LinkList* pphead, LinkList* pptail, ElemType i);
void list_sort_insert(LinkList* pphead, LinkList* pptail, ElemType i);
void list_delete(LinkList* pphead, LinkList* pptail, ElemType i);
void list_modify(LinkList phead, ElemType i, float score);