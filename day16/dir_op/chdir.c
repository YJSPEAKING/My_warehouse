#include<unistd.h>
#include<stdio.h>
int main()
{
	char buf[512]={0};
	//获取当前路径，填到buf里
	getcwd(buf,sizeof(buf));
	puts(buf);
	chdir("../");//改变路径到上一级
	//系统会给你空间
	puts(getcwd(NULL,0));
	return 0;
}
