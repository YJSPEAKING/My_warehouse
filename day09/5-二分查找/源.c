#include <stdio.h>

#define N 10

int binarySearch(int* a, int low, int high, int target)
{
	int mid;
	while (low <= high)
	{
		mid = (low + high) / 2;
		if (a[mid] < target)
		{
			low = mid + 1;
		}
		else if (a[mid] > target)
		{
			high = mid - 1;
		}
		else {
			return mid;
		}
	}
	return -1;
}
int main()
{
	int a[N] = { 6, 15 ,18 ,24 ,26 ,57 ,58, 73, 91 ,96 };
	int pos;
	pos = binarySearch(a, 0, N - 1, 24);
	printf("pos=%d\n", pos);
	return 0;
}