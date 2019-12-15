#include "DList.hpp"
void TestDList()
{
	DList<int> s1;
	DList<int> s2(s1);
	DList<int> s3=s1;
	s1.DListPushBack(1);
	s1.DListPushBack(2);
	s1.DListPushBack(3);
	s1.DListPushBack(4);
	s1.DListPushBack(5);
	s1.PrintDList();
	s1.DListPopBack();
	s1.PrintDList();
	s1.DListPushFront(0);
	s1.PrintDList();
	s1.DListPopFront();
	s1.PrintDList();
	s1.DListInsert(s1.Find(2), 0);
	s1.PrintDList();
	s1.DListErase(s1.Find(0));
	s1.PrintDList();
	int size = s1.DListSize();
	cout << size << endl;
	int data = s1.DListFront();
	cout << data << endl;
	data = s1.DListBack();
	cout << data << endl;
}
int main()
{
	TestDList();
	return 0;
}
