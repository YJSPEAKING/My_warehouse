#include <stdio.h>

void error1()
{
	printf("\n");//���ܰ�printf���˫����дΪ������
}

void error2()
{
	char c;
	while ((c = getchar()) != EOF)
	{
		if (c != '\n')
		{
			printf("%c", c - 32);
		}
		else {
			printf("\n");
			break;
		}
	}
}

void error3()
{
	while (1)
		printf("I am niu\n");
		printf("I am niu2\n");
}

int main()
{
	error3();
	return 0;
}