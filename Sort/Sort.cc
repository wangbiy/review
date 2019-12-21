#include <iostream>
using namespace std;
void Print(int* arr,int size)
{
	for(int i=0;i<size;++i)
	{
		cout<<arr[i]<<" ";
	}
	cout<<endl;
}
//直接选择排序
void InsertSort(int* arr,int size)
{
	for(int i=1;i<size;++i)
	{
		int k=arr[i];
		int end=i-1;
		while(end>=0 && k<arr[end])
		{
			arr[end+1]=arr[end];
			end--;
		}
		arr[end+1]=k;
	}
}
//希尔排序
void SortWithGap(int* arr,int size,int gap)
{
	for(int i=gap;i<size;++i)
	{
		int k=arr[i];
		int end=i-gap;
		while(end>=0 && k<arr[end])
		{
			arr[end+gap]=arr[end];
			end-=gap;
		}
		arr[end+gap]=k;
	}
}
void ShellSort(int* arr,int size)
{
	int gap=size;
	while(1)
	{
		gap=gap/3+1;
		SortWithGap(arr,size,gap);
		if(gap==1)
			break;
	}
}
int main()
{
	int arr[]={1,8,7,9,10,0,24,76,2};
	InsertSort(arr,sizeof(arr)/sizeof(arr[0]));
	Print(arr,sizeof(arr)/sizeof(arr[0]));
	ShellSort(arr,sizeof(arr)/sizeof(arr[0]));
	Print(arr,sizeof(arr)/sizeof(arr[0]));
	return 0;
}
