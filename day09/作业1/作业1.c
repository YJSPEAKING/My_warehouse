//大根堆的调整
void adjustMaxheap(int* a, int len, int adjroot) {
	int dad = adjroot;
	int son = 2 * adjroot + 1;
	while (son < len) {
		if (son + 1 < len && a[son] < a[son + 1]) {//在左右孩子中选出大的那一个
			son++;
		}
		if (a[son] > a[dad]) {
			swap(a[son], a[dad]); //若父节点元素小于儿结点，则交换两元素并向下调整
			dad = son;
			son = 2 * dad + 1;
		}
		else {
			break;
		}
	}
}

//堆排，大根堆为例
void heapsort(int* a) {
	int i;
	for (i = MaxSize / 2 - 1; i >= 0; i--) {//编号从下标0开始,从n/2个结点开始下坠调整为大根堆
		adjustMaxheap(a, MaxSize, i);
	}
	for (i = 0; i < MaxSize; i++) {        //交换堆顶和堆底元素，并重新调整为大根堆
		swap(a[0], a[MaxSize - 1 - i]);
		adjustMaxheap(a, MaxSize - 1 - i, 0);
	}
}

qsort(a, MaxSize, sizeof(int), compare);
//qsort 比较函数
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