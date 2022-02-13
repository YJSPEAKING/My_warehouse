#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
typedef char ElemType;
typedef struct node {
	ElemType c;
	struct node* left;
	struct node* right;
}Node_t,*pNode_t;

typedef struct queue_t {
	pNode_t insertPos;
	struct queue_t* pnext;
}Queue_t,*pQueue_t;

void buildBinaryTree(pNode_t* treeRoot, pQueue_t* queHead, 
	pQueue_t* queTail, ElemType val);
void preOrder(pNode_t treeRoot);
void midOrder(pNode_t treeRoot);
void latOrder(pNode_t treeRoot);