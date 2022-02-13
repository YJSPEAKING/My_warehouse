#include<unistd.h>
#include<stdio.h>
int main()
{
	char buf[512]={0};
	//获取当前路径，填到buf里
	getcwd(buf,sizeof(buf));
	puts(buf);
	return 0;
}
