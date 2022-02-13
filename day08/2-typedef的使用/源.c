#include <stdio.h>

//typedef目的1：省去每此都要写struct student的麻烦
typedef struct student//结构体中不含struct student*的时候可以去掉student
{
	int num;
	char name[20];
	char sex;
}stu,*pstu;

//typedef目的2：代码即注释
//typedef目的3：省去批量修改int为其他数据类型的麻烦
typedef int ELEMTYPE;

//不要让变量名和结构体类型重名
//即不要定义一个pstu stu
int main()
{
	stu s = { 101 };
	pstu p;
	ELEMTYPE i;
	p = &s;
	printf("%d %s %c\n", p->num, p->name, p->sex);//没定义的结构体部分默认为0
	return 0;
}