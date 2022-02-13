#include <stdio.h>
#define N 5
int bubble(int* a[])
{
	int i = 0;
	int b = 0;
	while (i < N - 1)
	{
		if (a[i] > a[i + 1])
		{
			b = a[i];
			a[i] = a[i + 1];
			a[i + 1] = b;
		}
		i++;
	}
}

int main()
{
	int a[N] = { 5,4,3,2,1 };
	bubble(&a);
	printf("max=%d\n", a[N - 1]);
	bubble(&a);
	printf("s_max=%d\n", a[N - 2]);
	return 0;
}