#include "mysort.h"

void bubble(int* a)
{
	int i, j,flag;
	for (i = N - 1; i >0 ; i--)
	{
		flag = 1;
		for (j = 0; j < i; j++)
		{
			if (a[j] > a[j + 1])
			{
				SWAP(a[j], a[j + 1]);
				flag = 0;
			}
		}
		if (flag)//ð��������ǰ����
		{
			break;
		}
	}
}


void select(int* a)
{
	int i, j, min_pos;
	for (i=0;i<N-1;i++)
	{
		min_pos = i;
		for (j = i+1; j < N; j++)
		{
			if (a[j] < a[min_pos])
			{
				min_pos = j;
			}
		}
		SWAP(a[min_pos], a[i]);
	}
}

void insert(int* a)
{
	int i, j,insert_val;
	for (i = 1; i < N; i++)//������Ҫ���Ǹ���ȥ����
	{
		insert_val = a[i];
		for (j = i - 1; j >= 0; j--) //����������������
		{
			if (a[j] > insert_val)//������������
			{
				a[j + 1] = a[j];
			}
			else {//��������ھ�break
				break;
			}
		}
		a[j + 1] = insert_val;
	}
}


void shell(int* a)
{
	int i, j, insert_val,gap;
	for(gap=N/2;gap>0;gap>>=1)
	{ 
		for (i = gap; i < N; i++)//������Ҫ���Ǹ���ȥ����
		{
			insert_val = a[i];
			for (j = i - gap; j >= 0&& a[j] > insert_val; j-=gap) //����������������
			{
				a[j + gap] = a[j];
			}
			a[j + gap] = insert_val;
		}
	}
}

int partition(int* a, int left, int right)
{
	//������д������
	int i, k;//right���ұ��Ƿָ�ֵ
	for (i=k=left; i < right; i++)
	{
		if (a[i] < a[right])
		{
			SWAP(a[i], a[k]);
			k++;
		}
	}
	SWAP(a[k], a[right]);
	return k;
}
//����
void quick(int* a,int left,int right)
{
	int pivot;//�ָ�ֵ���±�
	if (left < right)
	{
		pivot = partition(a, left, right);
		quick(a, left, pivot - 1);
		quick(a, pivot + 1, right);
	}
}

//����ĳ������Ϊ�����
//�ѵĸ��Ǵ����±꿪ʼ��������son = 2 * dad + 1
//�ѵĸ��Ǵ�1�±꿪ʼ��������son = 2 * dad
void adjustMaxHeap(int* a, int adjustPos, int len)
{
	int dad = adjustPos;
	int son = 2 * dad + 1;//���ӵ��±�
	while (son<len)//sonҪС�����鳤��
	{
		//�ȱȽ����Ӻ��Һ��ӣ�˭��˭�ͺ͸��ױȽ�
		if (son + 1 < len && a[son + 1]>a[son])
		{
			son++;
		}
		//�ô�ĺ��Ӻ͸��ױȽϣ��ȸ��״�Ҫ��������
		if (a[son] > a[dad])
		{
			SWAP(a[son], a[dad]);
			dad = son;
			son= 2 * dad + 1;
		}
		else {
			break;
		}
	}
}

void heap(int* a)
{
	int i;
	//����Ϊ�����
	for (i = N / 2 - 1; i >= 0; i--)
	{
		adjustMaxHeap(a, i, N);
	}
	//�����Ѷ���β��Ԫ��
	SWAP(a[0], a[N - 1]);
	for (i = N - 1; i > 1; i--)
	{
		adjustMaxHeap(a, 0, i);//��ʣ��Ԫ�ص���Ϊ�����
		SWAP(a[0], a[i-1]);//�Ѷ���Ԫ�غ����һ��Ԫ�ؽ���
	}
}

void merge_arr(int *a, int low, int mid, int high)
{
	int b[N];
	int i, j,k;
	for (i = low; i <= high; i++)//��a����b
	{
		b[i] = a[i];
	}
	for (i = low, j = mid + 1,k=low; i <= mid && j <= high;k++)
	{
		if (b[j] <= b[i])
		{
			a[k] = b[j];
			j++;
		}
		else if (b[i] < b[j])
		{
			a[k] = b[i];
			i++;
		}
	}
	//��Ҫ��ʲô
	while (i <= mid)
	{
		a[k] = b[i];
		k++;
		i++;
	}
	while (j <= high)
	{
		a[k] = b[j];
		k++;
		j++;
	}
}

//�鲢����
void merge(int* a, int low, int high)
{
	if (low < high)
	{
		int mid = (low + high) / 2;
		merge(a, low, mid);
		merge(a, mid + 1, high);
		merge_arr(a, low, mid, high);
	}
}

//��������
void count(int* a)
{
	int count[M] = { 0 };
	int i,j,k;
	for (i = 0; i < N; i++)
	{
		count[a[i]]++;
	}
	k = 0;
	for (i = 0; i < M; i++)//�������ȥ
	{
		for (j = 0; j < count[i]; j++)
		{
			a[k++] = i;
		}
	}
}

void print(int* a)
{
	int i;
	for (i = 0; i < N; i++)
	{
		printf("%3d", a[i]);
	}
	putchar('\n');
}