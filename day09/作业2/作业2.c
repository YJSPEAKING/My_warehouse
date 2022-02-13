void countSort(int a[])
{
	int count[M] = { 0 };
	int i, j, k = 0;
	for (i = 0; i < N; i++)
	{
		count[a[i]]++;
	}
	for (i = 0; i < M; i++)
	{
		for (j = 0; j < count[i]; j++)
		{
			a[k++] = i;
		}
	}
}