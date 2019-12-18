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
		int k=a[i];
		int end=i-1;
		while(end>=0 && k<a[end])
		{
			a[end+1]=a[end];
			end--;
		}
		a[end+1]=k;
	}
}
//希尔排序
void SortWithGap(int* a,int size)
{

}
int main()
{

}
