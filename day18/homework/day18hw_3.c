#include<func.h>
typedef struct student{
    int num;
    char name[20];
    int score;
}stu;
int main(int argc,char* argv[])
{
    ARGS_CHECK(argc,2);
    int fd;
    fd=open(argv[1],O_RDWR);
    ERROR_CHECK(fd,-1,"open");
    stu stu_arr[3]={1001,"zhangsan",99,1002,"lisi",98,1003,"wangwu",97};
    int i;
    for(i=0;i<3;i++)
    {
        write(fd,&stu_arr[i].num,sizeof(int));
        write(fd,stu_arr[i].name,20*sizeof(char));//不需要取址符
        write(fd,&stu_arr[i].score,sizeof(int));
    }
    lseek(fd,0,SEEK_SET);
    int num,score;//定义num，score和name[20]相当于缓冲区
    char name[20];
    for(i=0;i<3;i++)
    {   
        read(fd,&num,sizeof(int));
        read(fd,name,20*sizeof(char));
        read(fd,&score,sizeof(int));
        printf("%d %-15s %d\n",num,name,score);
    }
    close(fd);
    return 0;
}