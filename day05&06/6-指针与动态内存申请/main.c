#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main()
{
	int n;//ʹ�ö����ֽڿռ�
	int* p1;//int��p1������
	void* p;//p��������ָ��
	scanf("%d", &n);//��ȡҪ����ռ��С
	p = (char*)malloc(n);//����
						 //sizeof(p)=4  ָ�붼��4�ֽ�
	strcpy(p, "hello");
	puts(p);
	free(p);//p����ƫ�ƣ����������malloc���صĵ�ַ
			//���ں����м�¼����Ŀռ��С������Ҫ�������Ĵ�С
			//�ڴ�й©:�������Ѷ�̬����Ķ��ڴ�δ�ͷţ����³������б����Ƚ��
			//free����ֵΪvoid����Ϊfreeֻ��ɹ�����ʧ��
			//û����free������ı�p
	p = NULL;//����p��ΪNULL��p�ͱ����һ����Ұָ�롱
	return 0;
}