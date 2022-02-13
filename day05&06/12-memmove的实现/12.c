#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void* mymemmove(void* to, const void* from, size_t count)
{
	char* pto = (char*)to;
	char* pfrom = (char*)from;
	int i = 0;
	if (pto > pfrom)//从后往前copy
	{
		while (count > 0)
		{
			*(pto + count - 1) = *(pfrom + count - 1);
			count--;
		}
	}
	else if (pto < pfrom) //从前往后copy
	{
		while (i < count)
		{
			*(pto + i) = *(pfrom + i);
			i++;
		}
	}
}

int main()
{
	int a[10] = { 1,2,3,4,5 };
	mymemmove(a + 2, a, 20);
	mymemmove(a + 3, a + 4, 12);
	return 0;
}