#include<stdio.h>
int main()
{
	int a[1001] = { 999 };
	int sum = a[0];
	for (int i = 1; i < 1001; i++)
	{
		a[i] = i;
	}
	for (int i = 1; i < 1001; i++)
	{
		sum += a[i]-i;
	}
	printf("repeat is %d\n", sum);
	return 0;
}