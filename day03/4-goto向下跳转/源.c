#include <stdio.h>
//������ת��Ϊ�˿��ٵ������ܶ��֧��ֱ���ߵ������Ĵ��󲿷�
int main()
{
	int disk=0;
	if (0==disk)
	{
		goto label_disk_error;
	}
	//д����
	printf("I am writing disk\n");
label_disk_error:
	printf("disk error\n");
	return 0;
}