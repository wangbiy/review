#include <stdio.h>
void swap(char *buf1, char *buf2, size_t width)
{
	size_t i = 0;
	for (i = 0; i < width; i++)
	{
		char tmp = *buf1;
		*buf1 = *buf2;
		*buf2 = tmp;
		buf1++;
		buf2++;
	}
}
int cmp_int(const void *e1, const void *e2)//e1,e2要比较的两个元素
{
	return *(int*)e1 - *(int*)e2;
}
void bubble_sort(void *base, size_t sz, size_t width,
		int(*cmp)(const void *e1, const void *e2))//函数指针
{
	size_t i = 0;
	for (i = 0; i < sz - 1; i++)
	{
		size_t j = 0;
		for (j = 0; j < sz - 1 - i; j++)
		{
			if (cmp((char*)base + j*width, (char*)base + (j + 1)*width)>0)
			{
				swap((char*)base + j*width, (char*)base + (j + 1)*width, width);
			}
		}
	}
}
int main()
{
	int arr[]={1,3,2,4,15,6,7,10,8};
	bubble_sort(arr,sizeof(arr)/sizeof(arr[0]),sizeof(int),cmp_int);
	size_t i=0;
	for(;i<sizeof(arr)/sizeof(arr[0]);++i)
	{
		printf("%d ",arr[i]);
	}
	printf("\n");
	return 0;
}
