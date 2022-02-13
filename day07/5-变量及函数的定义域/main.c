#include "func.h"
static int k = 10;
int main()
{
	int i = 10;
	{
		int j = 5;//j是在大括号外不能访问的
	}
	printf("i=%d\n", i);
	printf("main k=%d\n", k);
	print();
	print();
	return 0;
}