#include "SList.hpp"
void menu()
{
	cout<<"**           1.尾插                2.尾删                 **"<<endl;
	cout<<"**           3.头插                4.头删                 **"<<endl;
	cout<<"**           5.任意位置插入        6.任意位置删除         **"<<endl;
	cout<<"**           7.结点个数            8.返回第一个值         **"<<endl;
	cout<<"**           9.返回最后一个值      10.显示                **"<<endl;
	cout<<"**           11.逆置               12.判空                **"<<endl;
}
void TestSList()
{
	SList<int> sl;
	int data=0;
	int val=0;
	int count=0;
	int input=0;
	do
	{
		menu();
		cout<<"请选择:>";
		cin>>input;
		switch(input)
		{
			case 1:
				cout<<"请输入要插入的数:>";
				cin>>data;
				sl.SListPushBack(data);
				break;
			case 2:
				sl.SListPopBack();
				break;
			case 3:
				cout<<"请输入要插入的数:>";
				cin>>data;
				sl.SListPushFront(data);
				break;
			case 4:
				sl.SListPopFront();
				break;
			case 5:
				cout<<"请输入要插入到哪个数后面:>";
				cin>>val;
				cout<<"请输入要插入的数:>";
				cin>>data;
				sl.SListInsertAfter(sl.SListFind(val),data);
				break;
			case 6:
				cout<<"请输入要删除的数:>";
				cin>>data;
				sl.SListErase(sl.SListFind(data));
				break;
			case 7:
				count=sl.SListSize();
				cout<<"结点个数是:"<<count<<endl;
				break;
			case 8:
				data=sl.SListFront();
				cout<<"第一个值为:"<<data<<endl;
				break;
			case 9:
				data =sl.SListBack();
				cout<<"最后一个值为:"<<data<<endl;
			case 10:
				sl.PrintSList();
				break;
			case 11:
				sl.ReverseSList();
				break;
			case 12:
				sl.SListEmpty();
				break;
		}
	}while(input);
}
int main()
{
	TestSList();
	return 0;
}
