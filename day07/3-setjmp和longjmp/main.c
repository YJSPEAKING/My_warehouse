#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>

//ʹ��setjmp��longjmp�ﵽmain����A��A����B֮��Bһ������main����

void b(jmp_buf envbuf)
{
	printf("I am func b\n");
	longjmp(envbuf, 5);//�ص�envbuf�ֳ�
}

void a(jmp_buf envbuf)
{
	printf("before b,I am func a\n");
	b(envbuf);
	printf("after b,I am func a\n");
}

//�����ľ��ǵ�ǰ�Ĵ�����״̬
int main()
{
	int ret;
	jmp_buf envbuf;//jmp_buf��һ������
	ret = setjmp(envbuf);//�ѵ�ǰ��������
	if (0 == ret)
	{
		a(envbuf);
	}
	return 0;
}