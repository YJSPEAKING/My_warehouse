#include "tree.h"
//����
void buildBinaryTree(pNode_t* treeRoot, pQueue_t* queHead, pQueue_t* queTail, ElemType val)
{
	//�����������ռ�
	pNode_t treeNew = (pNode_t)calloc(1, sizeof(Node_t));
	treeNew->c = val;
	pQueue_t queNew = (pQueue_t)calloc(1, sizeof(Queue_t));
	queNew->insertPos = treeNew;
	pQueue_t queCur;
	//�ж����Ƿ�Ϊ��
	if (NULL == *treeRoot)
	{
		*treeRoot = treeNew;
		*queHead = queNew;
		*queTail = queNew;
	}
	else {
		//���
		(*queTail)->pnext = queNew;
		*queTail = queNew;
		//�ж�ĳ�������������Ƿ�Ϊ��,�������
		if (NULL==(*queHead)->insertPos->left)
		{
			(*queHead)->insertPos->left = treeNew;
		}
		else if (NULL == (*queHead)->insertPos->right)////�ж�ĳ���������Һ����Ƿ�Ϊ��
		{
			(*queHead)->insertPos->right = treeNew;
			//��ĳ����������Һ��Ӷ����ˣ�����
			queCur = *queHead;
			*queHead = queCur->pnext;
			free(queCur);
			queCur = NULL;
		}
	}
}

//ǰ�������������ȱ���
void preOrder(pNode_t treeRoot)
{
	if(treeRoot)
	{
		putchar(treeRoot->c);
		preOrder(treeRoot->left);
		preOrder(treeRoot->right);
	}
}
//�������
void midOrder(pNode_t treeRoot)
{
	if (treeRoot)
	{
		midOrder(treeRoot->left);
		putchar(treeRoot->c);
		midOrder(treeRoot->right);
	}
}


//��������
void latOrder(pNode_t treeRoot)
{
	if (treeRoot)
	{
		latOrder(treeRoot->left);
		latOrder(treeRoot->right);
		putchar(treeRoot->c);
	}
}