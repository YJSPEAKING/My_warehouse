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
	long long l2;//8���ֽڣ�64λ��Ҳ��8���ֽ�
	short a, b;
	a = 32767;
	b = a + 1;//�������,����Ľ���취�������ռ��С
	printf("b=%d\n", b);
	unsigned int m = 0x80000000;
	printf("m=%u\n", m);
}

void float_exercise()
{
	float f = 4.5;//e��10���ݴ�
	double a, b;
	a = 1.23456789e10;//12345678900
	b = a + 20;
	printf("b=%0.1f\n", b);//12345678920
}

void char_exercise()
{
	char c = 'a';
		printf("%c\n", c);//�õ������ַ�a
	printf("%d\n", c);//�õ���a��ASCII��97
	printf("abc\rd\n");//"\r"�ù��ص��ʼ��d��a���ǣ��õ�dbc
	printf("abc\bd\n");//"\b"�ù����ǰһ��d��b���ǣ��õ�abd
	printf("\\\n");//���"\"
}

//�������
//��������Ĭ�ϰ�int����
void mix_calc()
{
	char b = 0x93 <<1 >>1;
	printf("%x\n",b);
	b = 0x93 << 1;//���ƺ�ᶪʧ��λ��1
	b = b >> 1;
	printf("%x\n", b);
}

void mix_calc2()
{
	long long m;
	m = (long long)131072 * 131072;
	//����ǿ��ת����������������Ĭ�ϰ�int���㣬ֻ��4���ֽڵ�ֵ�ḳֵ��m
	printf("%lld\n", m);//32λ����longlongҪ��lld
}

//�����ͳ���Ĭ�ϰ�double����
void mix_calc3()
{
	float f = 1234567890.0;
	printf("%f\n", f);
	printf("%f\n", 1234567890.0);
	f = 1.456;//floatf�Ὣ1.456��double���ȶ�ʧ
	double d = 1.456;
	if (f == 1.456)//f����1.456�������Ѷ�ʧ
	{
		printf("f is equel to 1.456\n");
	}
	if (f - 1.456 > -0.0001 && f - 1.456 < 0.0001)//���÷�Χ��ע����
	{
		printf("f is near 1.456\n");
	}
}

void mix_calc4()
{
	int i = 5;
	float f = (float)i / 2;	//�����ǿ��ת����i/2����2����2.5
	printf("%f\n", f);
	long l = 10;
	short s = 0;
	s = (short)l;//ʹ��ǿ������ת��ȥ������
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
	return 0;//main����������return
}