//����ѵĵ���
void adjustMaxheap(int* a, int len, int adjroot) {
	int dad = adjroot;
	int son = 2 * adjroot + 1;
	while (son < len) {
		if (son + 1 < len && a[son] < a[son + 1]) {//�����Һ�����ѡ�������һ��
			son++;
		}
		if (a[son] > a[dad]) {
			swap(a[son], a[dad]); //�����ڵ�Ԫ��С�ڶ���㣬�򽻻���Ԫ�ز����µ���
			dad = son;
			son = 2 * dad + 1;
		}
		else {
			break;
		}
	}
}

//���ţ������Ϊ��
void heapsort(int* a) {
	int i;
	for (i = MaxSize / 2 - 1; i >= 0; i--) {//��Ŵ��±�0��ʼ,��n/2����㿪ʼ��׹����Ϊ�����
		adjustMaxheap(a, MaxSize, i);
	}
	for (i = 0; i < MaxSize; i++) {        //�����Ѷ��Ͷѵ�Ԫ�أ������µ���Ϊ�����
		swap(a[0], a[MaxSize - 1 - i]);
		adjustMaxheap(a, MaxSize - 1 - i, 0);
	}
}

qsort(a, MaxSize, sizeof(int), compare);
//qsort �ȽϺ���
int compare(const void* low, const void* high) {
	int* x = (int*)low;
	int* y = (int*)high;
	if (*x > *y) {
		return 1;
	}
	else if (*x < *y) {
		return -1;
	}
	else {
		return 0;
	}
}