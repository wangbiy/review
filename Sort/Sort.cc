#include <iostream>
using namespace std;
#include <string.h>
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
//冒泡排序
void BubbleSort(int* arr,int size)
{
	for(int i=0;i<size;++i)//趟数
	{
		int flag=0;
		for(int j=0;j<size-i-1;++j)
		{
			if(arr[j]>arr[j+1])
			{
				swap(arr[j],arr[j+1]);
				flag=1;
			}
		}
			if(flag==0)
				break;
	}
}
//快速排序
int Partition1(int* arr,int left,int right)
{
	int begin=left;
	int end=right;
	int pivot=arr[right];
	while(begin<end)
	{
		while(begin<end && arr[begin]<=pivot)
		{
			begin++;
		}
		while(begin<end && arr[end]>=pivot)
		{
			end--;
		}
		swap(arr[begin],arr[end]);//这样小的一定在左边，大的一定在右边 
	}
	swap(arr[begin],arr[right]);//交换后基准值左边一定比他小，右边一定比他大
	return begin;
}
int Partition2(int* arr,int left,int right)
{
	int begin=left;
	int end=right;
	int pivot=arr[right];
	while(begin<end)
	{
		while(begin<end && arr[begin]<=pivot)
		{
			begin++;
		}
		arr[end]=arr[begin];
		while(begin<end && arr[end]>=pivot)
		{
			end--;
		}
		arr[begin]=arr[end];
	}
	arr[begin]=pivot;
    return begin;	
}
int Partition3(int* arr,int left,int right)
{
	int div=left;
	for(int i=left;i<right;++i)
	{
		if(arr[i]>arr[right])
		{
			swap(arr[i],arr[div]);
		}
		else
			div++;
	}
	swap(arr[div],arr[right]);
	return div;
}
void QuickSortInternal1(int* arr,int left,int right)
{
	if(left>=right)
		return;
	int pivotindex=Partition1(arr,left,right);//分组
	QuickSortInternal1(arr,left,pivotindex-1);
	QuickSortInternal1(arr,pivotindex+1,right);
}
void QuickSortInternal2(int* arr,int left,int right)
{
	if(left>=right)
		return;
	int pivotindex=Partition2(arr,left,right);//分组
	QuickSortInternal2(arr,left,pivotindex-1);
	QuickSortInternal2(arr,pivotindex+1,right);
}
void QuickSortInternal3(int* arr,int left,int right)
{
	if(left>=right)
		return;
	int pivotindex=Partition3(arr,left,right);//分组
	QuickSortInternal3(arr,left,pivotindex-1);
	QuickSortInternal3(arr,pivotindex+1,right);
}
void QuickSort1(int* arr,int size)
{
	QuickSortInternal1(arr,0,size-1);
}
void QuickSort2(int* arr,int size)
{
	QuickSortInternal2(arr,0,size-1);
}
void QuickSort3(int* arr,int size)
{
	QuickSortInternal3(arr,0,size-1);
}
//归并排序
void MergeData(int* arr,int left,int mid,int right,int* tmp)//按组排序
{
	int begin1=left;
	int end1=mid;
	int begin2=mid;
	int end2=right;
	int index=left;
	while(begin1<end1 && begin2<end2)
	{
		if(arr[begin1]<=arr[begin2])
			tmp[index++]=arr[begin1++];
		else
		    tmp[index++]=arr[begin2++];	
	}
	while(begin1<end1)
	{
		tmp[index++]=arr[begin1++];
	}
	while(begin2<end2)
	{
		tmp[index++]=arr[begin2++];
	}
	memcpy(arr+left,tmp+left,(right-left)*sizeof(arr[0]));
}
void _MergeSort(int* arr,int left,int right,int* tmp)
{
	if(left>=right-1)
		return;
	int mid=left+((right-left)>>1);
	_MergeSort(arr,left,mid,tmp);
	_MergeSort(arr,mid,right,tmp);
	MergeData(arr,left,mid,right,tmp);
}
void MergeSort(int* arr,int size)
{
	int* tmp=new int[size+1];
	_MergeSort(arr,0,size-1,tmp);
	delete[] tmp;
}
#include <assert.h>
//非比较排序
void CountSort(int* arr,int size)
{
	int minvalue=arr[0];
	int maxvalue=arr[0];
	for(int i=1;i<size;++i)
	{
		if(arr[i]>maxvalue)
			maxvalue=arr[i];
		if(arr[i]<minvalue)
		    minvalue=arr[i];
	}
	int range=(maxvalue-minvalue)+1;
	int* temp=(int*)malloc(range*sizeof(int));
	assert(temp);
	memcpy(temp,0,range*sizeof(int));
	for(int i=0;i<size;++i)
	{
		temp[arr[i]-minvalue]++;
	}
	int index=0;
	for(int i=0;i<size;++i)
	{
		int count=temp[i];
		while(count--)
		{
			arr[index++]=i+minvalue;
		}
	}
	free(temp);
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
	BubbleSort(arr,sizeof(arr)/sizeof(arr[0]));
	Print(arr,sizeof(arr)/sizeof(arr[0]));
	QuickSort1(arr,sizeof(arr)/sizeof(arr[0]));
	Print(arr,sizeof(arr)/sizeof(arr[0]));
	QuickSort2(arr,sizeof(arr)/sizeof(arr[0]));
	Print(arr,sizeof(arr)/sizeof(arr[0]));
	QuickSort3(arr,sizeof(arr)/sizeof(arr[0]));
	Print(arr,sizeof(arr)/sizeof(arr[0]));
	MergeSort(arr,sizeof(arr)/sizeof(arr[0]));
	Print(arr,sizeof(arr)/sizeof(arr[0]));
	CountSort(arr,sizeof(arr)/sizeof(arr[0]));
	Print(arr,sizeof(arr)/sizeof(arr[0]));
	return 0;
}
