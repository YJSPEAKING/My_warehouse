#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
void inverse(char c[], int i)//我这个递归写太妙了！我真聪明！
{
	int j = i;
	while(c[j])
	{
		if ((c[j] == 32 && (c[j + 1] != 32||!c[j+1])) || (c[j] != 32 && (c[j + 1] == 32||!c[j+1])))
			//必须让最后一个元素符合这些条件，不是为了让它进递归，而是为了让它打印出来
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