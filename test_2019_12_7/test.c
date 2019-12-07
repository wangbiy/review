#include <stdio.h>
int Add(int a,int b)
{
    return a+b;
}
int Sub(int a,int b)
{
    return a-b;
}
int Mul(int a,int b)
{
    return a*b;
}
int Div(int a,int b)
{
    return a/b;
}
int main()
{
    int x,y;
    int input=1;
    int ret=0;
    //使用函数指针数组构造转移表
    int (*p[5])(int x,int y)={0,Add,Sub,Mul,Div};
    while(input)
    {
        printf("***************************\n");
        printf("**1.Add             2.Sub**\n");
        printf("**3.Mul             4.Div**\n");
        printf("***************************\n");
        printf("请选择:>");
        scanf("%d",&input);
        if(input<=4&&input>=1)
        {
            printf("请输入操作数:>");
            scanf("%d %d",&x,&y);
            ret=(*p[input])(x,y);
        }
        else
            printf("输入有误!\n");
        printf("%d\n",ret);
    }
    return 0;
}
