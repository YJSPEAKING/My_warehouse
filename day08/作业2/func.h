#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

typedef struct LNode
{
	int data;
	struct LNode* next;
}LNode, * LinkList;

void list_head_insert(LinkList* pphead, LinkList* pptail, int n);
void list_tail_insert(LinkList* pphead, LinkList* pptail, int n);
void list_sort_insert(LinkList* pphead, LinkList* pptail, int n);
void list_delete(LinkList* pphead, LinkList* pptail, int n);
void print_list(LinkList phead);