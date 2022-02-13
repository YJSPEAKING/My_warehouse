#include <stdio.h>
//release 模式下不会检测访问越界，而工作都是release
//在子函数中如何访问数组元素，并修改
void print_arr(int a[],int length)
{
	int i;
	for (i = 0; i < length; i++)
	{
		printf("%2d", a[i]);
	}
	printf("\n");
	a[3] = 20;
}
int main()
{
	int j = 10;
	int a[5]={ 1,2,3,4,5 };
	int i = 17;
	//a[5] = 6;//访问越界
	//a[6] = 7;
	//a[7] = 8;
	//printf("j=%d\n", j);
	print_arr(a,5);//a[5]只会将int*传过去
	printf("a[3]=%d\n", a[3]);
	return 0;
}