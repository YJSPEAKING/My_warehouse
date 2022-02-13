#include<stdio.h>
#define M 5
#define N 7
void intersection(int arr1[], int arr2[], int b[])
{
	int i = 0, j = 0;
	int k = 0;
	while (i < N && j < N)
	{
		while (arr1[i] < arr2[j] && i < N)
			i++;
		while (arr1[i] > arr2[j] && j < N)
			j++;
		while (arr1[i] == arr2[j] && i < N && j < N)
		{
			b[k++] = arr1[i++];
			j++;
		}
	}
}

int main()
{
	int arr[M][N] = { {1,2,3,4,5,6,7},{2,3,4,5,6,7,8},{3,4,5,6,7,8,9},{4,5,6,7,8,9,10},{5,6,7,8,9,10,11} };
	int b[M - 1][N] = { {0},{0},{0},{0} };
	int i = 2;
	intersection(arr[0], arr[1], b[0]);
	while (i < M)
	{
		intersection(arr[i], b[i-2], b[i-1]);
		i++;
	}
	i = 0;
	while (b[M - 2][i])
	{
		printf("%d",b[3][i++]);
	}
	return 0;
}