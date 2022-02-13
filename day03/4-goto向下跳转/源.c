#include <stdio.h>
//向下跳转是为了快速的跳过很多分支，直接走到函数的错误部分
int main()
{
	int disk=0;
	if (0==disk)
	{
		goto label_disk_error;
	}
	//写磁盘
	printf("I am writing disk\n");
label_disk_error:
	printf("disk error\n");
	return 0;
}