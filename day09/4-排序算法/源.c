#include "mysort.h"

//p1 ��p2������������Ԫ�صĵ�ֵַ
int compare(const void* p1, const void* p2)
{
	int* pleft = (int*)p1;
	int* pright = (int*)p2;
	//return *pleft - *pright;
	if (*pleft < *pright)
	{
		return -1;
	}
	else if (*pleft > *pright)
	{
		return 1;
	}
	else {
		return 0;
	}
}

int main()
{
	int i;
	int* a = (int*)malloc(N * sizeof(int));//������
	time_t start, end;//����1970 1��1�ŵ�����
	//int a[N] = { 3,87,2,93,78,56,61,38,12,40 };
	srand(time(NULL)); //��������   
	for (i = 0; i < N; i++)
	{
		a[i]=rand()%M;
	}
	//print(a);
	start = time(NULL);//��ȡ����1970 1��1�ŵ�����
	//bubble(a);
	//select(a);
	//insert(a);
	//shell(a);
	//qsort(a, N, sizeof(int), compare);
	//quick(a,0,N-1);
	//heap(a);
	//merge(a, 0, N - 1);
	count(a);
	end = time(NULL);
	printf("start=%lld,end=%lld,use time=%lld\n", start, end, end - start);
	print(a);
	return 0;
}