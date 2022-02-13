#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main()
{
	int arr[3] = { 0 };
	char c;
	char* p_arr[3] = { "alp","num","oth" };
	int i, j, tmp;
	char* ptmp;
	while ((c = getchar()) != EOF)
	{
		if (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z')
		{
			arr[0]++;
		}
		else if (c >= '0' && c <= '9')
		{
			arr[1]++;
		}
		else if (c != '\n') {
			arr[2]++;
		}
	}
	printf("alp=%d,num=%d,oth=%d\n", arr[0], arr[1], arr[2]);
	for (i = 2; i > 0; i--)
	{
		for (j = 0; j < i; j++)
		{
			if (arr[j] < arr[j + 1])
			{
				tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
				//同步交换字符串
				ptmp = p_arr[j];
				p_arr[j] = p_arr[j + 1];
				p_arr[j + 1] = ptmp;
			}
		}
	}
	printf("%s=%d,%s=%d,%s=%d\n", p_arr[0], arr[0], p_arr[1], arr[1], p_arr[2], arr[2]);
	//打柱形图
	for (i = 0; i <= arr[0]; i++)
	{
		//第一根柱子
		if (0 == i) {
			printf("%3d   ", arr[0]);
		}
		else {
			printf("***** ");
		}
		//第2根柱子
		if (i == arr[0] - arr[1])
		{
			printf("%3d   ", arr[1]);
		}
		else if (i > arr[0] - arr[1]) {
			printf("***** ");
		}
		//第3根柱子
		if (i == arr[0] - arr[2])
		{
			printf("%3d", arr[2]);
		}
		else if (i > arr[0] - arr[2]) {
			printf("*****");
		}
		printf("\n");
	}
	printf("%4s  %4s  %4s\n", p_arr[0], p_arr[1], p_arr[2]);//打印下面字符串
	return 0;
}