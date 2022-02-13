#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#define MAXKEY 1000//¹þÏ£±í³¤

int hash(char* key)
{
	int h = 0, g;
	while (*key)
	{
		h = (h << 4) + *key++;
		g = h & 0xf0000000;
		if (g)
		{
			h ^= g >> 24;
		}
		h &= ~g;
	}
	return h % MAXKEY;
}

int main()
{
	char* pStr[] = { "yangyijia", "huangyan", "luoxiang", "wangdao", "longge" };
	char* hashTable[MAXKEY] = { 0 };
	int i;
	for (i = 0; i < 5; i++)
	{
		printf("%s %d\n", pStr[i], hash(pStr[i]));
		hashTable[hash(pStr[i])] = pStr[i];
	}
	return 0;
}