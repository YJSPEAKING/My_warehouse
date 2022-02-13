#include<stdio.h>
#define N 10
int main()
{
	int a[N] = { 1,3,5,7,9,10,12,14,16,18 };
	int min = 10000;
	int x = 0, y = 0;
	for (int i = 0; i < N; i++)
	{
		for (int j = i+1; j < N; j++)
		{
			if (min > abs(a[i] - a[j]))
			{
				min = abs(a[i] - a[j]);
				x = i;
				y = j;
			}
		}
	}
	printf("min=%d x=%d y=%d", min, a[x], a[y]);
	return 0;
}