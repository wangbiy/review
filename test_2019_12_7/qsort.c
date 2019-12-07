#include <stdio.h>
//实现整形数组元素的排序
int int_cmp(const void* p1,const void* p2)
{
    return (*(int*)p1-*(int*)p2);
}
int main()
{
    int arr[]={1,3,4,6,2,7,9,0};
	int i=0;
	qsort(arr,sizeof(arr)/sizeof(arr[0]),sizeof(int),int_cmp);
	for(i=0;i<sizeof(arr)/sizeof(arr[0]);++i)
	{
		printf("%d",arr[i]);
	}
	printf("\n");
	return 0;
}
