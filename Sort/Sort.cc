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
//简单选择排序
void SelectSort1(int* arr,int size)
{
	for(int i=0;i<size;++i)//比较趟数
	{
		int max=0;//假设无序区间第一个数最大
		for(int j=1;j<size-i;++j)//无序区间
		{
			if(arr[j]>arr[max])
			{
				max=j;
			}
		}
		//最大的与无序区间最后一个交换
		int t=arr[max];
		arr[max]=arr[size-i-1];
		arr[size-i-1]=t;
	}
}
void SelectSort2(int* arr,int size)
{
	for(int i=0;i<size;++i)//比较的趟数
	{
		int min=i;//假设最小的是无序区间的第一个
		for(int j=1;j<size-i;++j)//无序区间
		{
			if(arr[j]<arr[min])
			{
				min=i;
			}
		}
		int t=arr[min];
		arr[min]=arr[i];
		arr[i]=t;
	}
}
void swap(int& a,int& b)
{
	int t=a;
	a=b;
	b=t;
}
void SelectSort3(int* arr,int size)
{
	int left=0;
	int right=size-1;
	while(left<right)
	{
		int min=left;
		int max=left;
		for(int i=left+1;i<=right;++i)
		{
			if(arr[i]<arr[min])
			{
				min=i;
			}
			if(arr[i]>arr[max])
			{
				max=i;
			}
		}
		swap(arr[min],arr[left]);
		if(max==left)
		{
			max=min;
		}
		swap(arr[max],arr[right]);
		left++;
		right--;
	}
}
//堆排序
void heapify(int* arr,int size,int index)
{
	int left=2*index+1;
	int right=2*index+2;
	if(left>=size)
		return;
	int max=left;
	if(right<size && arr[right]>arr[left])
	{
		max=right;
	}
	if(arr[index]>arr[max])
		return;
	swap(arr[index],arr[max]);
	heapify(arr,size,max);
}
void CreateHeap(int* arr,int size)
{
	for(int i=(size-1-1)/2;i>=0;--i)
	{
		heapify(arr,size,i);//建大堆
	}
}
void HeapSort(int* arr,int size)
{
	CreateHeap(arr,size);
	for(int i=0;i<size;++i)
	{
		swap(arr[0],arr[size-i-1]);
		heapify(arr,size-i-1,0);
	}
}
int main()
{
	int arr[]={1,8,7,9,10,0,24,76,2};
	InsertSort(arr,sizeof(arr)/sizeof(arr[0]));
	Print(arr,sizeof(arr)/sizeof(arr[0]));
	ShellSort(arr,sizeof(arr)/sizeof(arr[0]));
	Print(arr,sizeof(arr)/sizeof(arr[0]));
	SelectSort1(arr,sizeof(arr)/sizeof(arr[0]));
	Print(arr,sizeof(arr)/sizeof(arr[0]));
	SelectSort2(arr,sizeof(arr)/sizeof(arr[0]));
	Print(arr,sizeof(arr)/sizeof(arr[0]));
	SelectSort3(arr,sizeof(arr)/sizeof(arr[0]));
	Print(arr,sizeof(arr)/sizeof(arr[0]));
	HeapSort(arr,sizeof(arr)/sizeof(arr[0]));
	Print(arr,sizeof(arr)/sizeof(arr[0]));
	return 0;
}
