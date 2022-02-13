#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

int main()
{
	int a[5] = { 1,2,3,4,5 };
	int b[5];
	memcpy(b, a, sizeof(a));
	return 0;
}