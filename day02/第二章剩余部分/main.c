#include<stdio.h>

void buma()
{
	int i = -5;
	int j = 2;
}

void integer_type()
{
	int i;
	short s = 0x8000;
	long l;
	long long l2;//8个字节，64位下也是8个字节
	short a, b;
	a = 32767;
	b = a + 1;//发生溢出,溢出的解决办法是提升空间大小
	printf("b=%d\n", b);
	unsigned int m = 0x80000000;
	printf("m=%u\n", m);
}

void float_exercise()
{
	float f = 4.5;//e是10的幂次
	double a, b;
	a = 1.23456789e10;//12345678900
	b = a + 20;
	printf("b=%0.1f\n", b);//12345678920
}

void char_exercise()
{
	char c = 'a';
		printf("%c\n", c);//得到的是字符a
	printf("%d\n", c);//得到是a的ASCII码97
	printf("abc\rd\n");//"\r"让光标回到最开始，d将a覆盖，得到dbc
	printf("abc\bd\n");//"\b"让光标向前一格，d将b覆盖，得到abd
	printf("\\\n");//输出"\"
}

//混合运算
//整型运算默认按int运算
void mix_calc()
{
	char b = 0x93 <<1 >>1;
	printf("%x\n",b);
	b = 0x93 << 1;//左移后会丢失高位的1
	b = b >> 1;
	printf("%x\n", b);
}

void mix_calc2()
{
	long long m;
	m = (long long)131072 * 131072;
	//必须强制转换，否则整型运算默认按int运算，只有4个字节的值会赋值给m
	printf("%lld\n", m);//32位程序longlong要用lld
}

//浮点型常量默认按double运算
void mix_calc3()
{
	float f = 1234567890.0;
	printf("%f\n", f);
	printf("%f\n", 1234567890.0);
	f = 1.456;//floatf会将1.456的double精度丢失
	double d = 1.456;
	if (f == 1.456)//f不是1.456，精度已丢失
	{
		printf("f is equel to 1.456\n");
	}
	if (f - 1.456 > -0.0001 && f - 1.456 < 0.0001)//采用范围标注精度
	{
		printf("f is near 1.456\n");
	}
}

void mix_calc4()
{
	int i = 5;
	float f = (float)i / 2;	//如果不强制转换，i/2后是2而非2.5
	printf("%f\n", f);
	long l = 10;
	short s = 0;
	s = (short)l;//使用强制类型转换去除警告
}

int main()
{
	//buma();
	//integer_type();
	//float_exercise();
	//char_exercise();
	//mix_calc();
	//mix_calc2();
	mix_calc3();
	//mix_calc4();
	return 0;//main函数必须有return
}