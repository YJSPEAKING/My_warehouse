#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
void inverse(char c[], int i)//������ݹ�д̫���ˣ����������
{
	int j = i;
	while(c[j])
	{
		if ((c[j] == 32 && (c[j + 1] != 32||!c[j+1])) || (c[j] != 32 && (c[j + 1] == 32||!c[j+1])))
			//���������һ��Ԫ�ط�����Щ����������Ϊ���������ݹ飬����Ϊ��������ӡ����
		{
			inverse(c, j + 1);
			while (i <= j)
			{
				printf("%c", c[i]);
				i++;
			}
			return;
		}
		j++;
	}
}
int main()
{
	char c[100];
	gets(c);
	inverse(c, 0);
	return 0;
}