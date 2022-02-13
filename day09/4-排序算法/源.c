#include "mysort.h"

//p1 和p2代表任意两个元素的地址值
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
	int* a = (int*)malloc(N * sizeof(int));//存数组
	time_t start, end;//距离1970 1月1号的秒数
	//int a[N] = { 3,87,2,93,78,56,61,38,12,40 };
	srand(time(NULL)); //产生种子   
	for (i = 0; i < N; i++)
	{
		a[i]=rand()%M;
	}
	//print(a);
	start = time(NULL);//获取距离1970 1月1号的秒数
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