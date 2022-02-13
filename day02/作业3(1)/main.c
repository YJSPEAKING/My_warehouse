#include<stdio.h>
int main()
{
	int A[] = { 1,2,3,4,5,6 };
	int B[] = { 2,6,7,8,9 };
	int i = 0, j = 0;
	int m = 6, n = 5;//m、n分别表示A、B数组的元素个数
	while (i < m && j < n)
	{
		if (A[i] < B[j])
		{
			i++;
		}
		else if (A[i] == B[j])
		{
			printf("%d\n", A[i]);
			i++;
			j++;
		}
		else if (A[i] > B[j])
			j++;
	}
}