#include <stdio.h>
#include <string.h>
//实现整形数组元素的排序
//int int_cmp(const void* p1,const void* p2)
//{
    //return (*(int*)p1-*(int*)p2);
//}
struct S
{
	char name[20];
	int age;
};
//实现比较函数
void qsort(void* base,size_t num,size_t width,int (*cmp)(const void* e1,const void* e2));
int cmp_S_by_name(const void* e1,const void* e2)
{
	return strcmp(((struct S*)e1)->name,((struct S*)e2)->name);
}

int cmp_S_by_age(const void* e1,const void* e2)
{
	return (((struct S*)e1)->age-((struct S*)e2)->age);
}
void test1()
{
	struct S arr[3]={{"x",20},{"l",10},{"w",15}};
	qsort(arr,3,sizeof(struct S),cmp_S_by_name);
	for(int i=0;i<3;++i)
	{
		printf("%s ",arr[i].name);

	}
	printf("\n");
}
void test2()
{
	struct S arr[3]={{"x",20},{"l",10},{"w",15}};
	qsort(arr,3,sizeof(struct S),cmp_S_by_age);
	for(int i=0;i<3;++i)
	{
		printf("%d ",arr[i].age);
	}
	printf("\n");
}
int main()
{
	test1();
	test2();
   // int arr[]={1,3,4,6,2,7,9,0};
   // int i=0;
   // qsort(arr,sizeof(arr)/sizeof(arr[0]),sizeof(int),int_cmp);
   // for(i=0;i<sizeof(arr)/sizeof(arr[0]);++i)
   // {
   // 	printf("%d",arr[i]);
   // }
   // printf("\n");
	return 0;
}
