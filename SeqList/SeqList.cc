#include "SeqList.hpp"
void TestSeqList()
{
	int arr[10]={1,2,3,4,5,6,7,10,9,89};
	SeqList<int> s1(arr,sizeof(arr)/sizeof(int));
	SeqList<int> s2(s1);
	SeqList<int> s3=s2;
	s1.show();
	s2.show();
	s3.show();
	s1.PushBack(11);
	s1.show();
	s1.PopBack();
	s1.show();
	s1.PushFront(88);
	s1.show();
	s1.PopFront();
	s1.show();
	s1.Insert(4,12);
	s1.show();
	s1.Erase(4);
	s1.show();
	s1.SeqListRemove(7);
	s1.show();
	s1.RemoveAll(8);
	s1.show();
	int val=s1.SeqListFront();
	cout<<"s1的第一个元素是:"<<val<<endl;
	val=s1.SeqListBack();
	cout<<"s1的最后一个元素是:"<<val<<endl;

	cout<<"s1排序后的结果是:"<<endl;
	s1.SeqListSort();
	s1.show();

	val=s1.SeqListCapacity();
	cout<<"s1的容量是:"<<val<<endl;

	val=s1.SeqListSize();
	cout<<"s1的有效元素个数是:"<<val<<endl;
	s1.Empty();
}
int main()
{
	TestSeqList();
	return 0;
}
