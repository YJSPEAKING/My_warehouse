#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
int main()
{
	char c[100];
	char d[100];
	while (gets(c) != NULL)
	{
		printf("strlen=%d\n", strlen(c));
		strcpy(d, c);//c�е��ַ���copy��d
		puts(d);
		printf("strcmp=%d\n", strcmp("are", "how"));
		strcat(d, "hello");//�ַ���ƴ��
		puts(d);

	}
	return 0;
}