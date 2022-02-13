#include "tree.h"
//建树
void buildBinaryTree(pNode_t* treeRoot, pQueue_t* queHead, pQueue_t* queTail, ElemType val)
{
	//给树结点申请空间
	pNode_t treeNew = (pNode_t)calloc(1, sizeof(Node_t));
	treeNew->c = val;
	pQueue_t queNew = (pQueue_t)calloc(1, sizeof(Queue_t));
	queNew->insertPos = treeNew;
	pQueue_t queCur;
	//判断树是否为空
	if (NULL == *treeRoot)
	{
		*treeRoot = treeNew;
		*queHead = queNew;
		*queTail = queNew;
	}
	else {
		//入队
		(*queTail)->pnext = queNew;
		*queTail = queNew;
		//判断某个树结点的左孩子是否为空,放入左边
		if (NULL==(*queHead)->insertPos->left)
		{
			(*queHead)->insertPos->left = treeNew;
		}
		else if (NULL == (*queHead)->insertPos->right)////判断某个树结点的右孩子是否为空
		{
			(*queHead)->insertPos->right = treeNew;
			//当某个树结点左右孩子都有了，出队
			queCur = *queHead;
			*queHead = queCur->pnext;
			free(queCur);
			queCur = NULL;
		}
	}
}

//前序遍历，深度优先遍历
void preOrder(pNode_t treeRoot)
{
	if(treeRoot)
	{
		putchar(treeRoot->c);
		preOrder(treeRoot->left);
		preOrder(treeRoot->right);
	}
}
//中序遍历
void midOrder(pNode_t treeRoot)
{
	if (treeRoot)
	{
		midOrder(treeRoot->left);
		putchar(treeRoot->c);
		midOrder(treeRoot->right);
	}
}


//后续遍历
void latOrder(pNode_t treeRoot)
{
	if (treeRoot)
	{
		latOrder(treeRoot->left);
		latOrder(treeRoot->right);
		putchar(treeRoot->c);
	}
}