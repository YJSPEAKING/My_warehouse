#include<stdio.h>
int main()
{
	int A[] = { 1,2,3,4,5,6,7,8,9,10 };
	int B[] = { 2,6,7,8,9 };
	int C[] = { 3,6,9 };
	int i = 0, j = 0, k = 0;
	int l = 10, m = 5, n = 3;//l、m、n分别表示A、B、C数组的元素个数
	while (i < l && j < m && k < n)
	{
		if (A[i] < B[j] || A[i] < C[k])
			i++;
		if (B[j] < A[i] || B[j] < C[k])
			j++;
		if (C[k] < A[i] || C[k] < B[j])
			k++;
		else if (A[i] == B[j] && A[i] == C[k])
		{
			printf("%d\n", A[i]);
			i++;
			j++;
			k++;
		}
	}
	return 0;
}