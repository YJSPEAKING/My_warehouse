void merge(int a[], int low, int mid, int high)
{
	int i, j, k;
	int* B = (int*)malloc(N * sizeof(int));
	for (i = 0; i < N; i++)
	{
		B[i] = a[i];
	}
	for (i = low, j = mid + 1, k = i; i <= mid && j <= high; k++)
	{
		if (B[i] <= B[j])
		{
			a[k] = B[i++];
		}
		else
		{
			a[k] = B[j++];
		}
	}
	while (i <= mid)a[k++] = B[i++];
	while (j <= high)a[k++] = B[j++];
}
void mergeSort(int a[], int low, int high)
{
	int mid;
	if (low < high)
	{
		mid = (low + high) / 2;
		mergeSort(a, low, mid);
		mergeSort(a, mid + 1, high);
		merge(a, low, mid, high);
	}
}