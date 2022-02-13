#include <stdio.h>
#define M 5
int main()
{
	int arr[M] = { 1,9,6,1,1 };
	int i = 0;
	int max = arr[0];
	int count = 0;
	while (i < M)
	{
		if (arr[i] == max)
		{
			count++;
		}
		else
		{
			count--;
			if (count < 0)
			{
				max = arr[i];
				count = 1;
			}
		}
		i++;
	}
	printf("%d\n", max);
	return 0;
}