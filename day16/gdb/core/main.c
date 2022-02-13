#include<func.h>

void print(int i)
{
    printf("i=%d\n",i);
    char* p=NULL;
    *p=5;
    printf("*p=%d",*p);
}

int main(int argc,char* argv[])
{
    ARGS_CHECK(argc,3);
    int i=atoi(argv[1]);
    int j=atoi(argv[2]);
    int arr[5]={1,2,3,4,5};
    for(i=0;i<5;i++)
    {
        printf("%3d\n",arr[i]);
    }
    putchar('\n');
    print(i);
	return 0;
}
