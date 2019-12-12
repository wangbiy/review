#include "SeqList.h"
void SeqList:: show()//打印
{
	if(_size>0)//顺序表不为空
	{
		for(int i=0;i<_size;++i)
		{
			cout<<_arr[i]<<" ";
		}
		cout<<endl;
	}
	else
		cout<<"顺序表为空"<<endl;
}
static void CheckCapacity()
{
	if(_size==_capacity)
	{
		int newCapacity=_Capacity*2;
		T* pTemp=new T[newCapacity];
		memcpy(pTemp,_arr,_size*sizeof(_arr[0]));
		delete[]_arr;
		_arr=pTemp;
		_Capacity=newCapacity;
		cout<<"扩容成功"<<endl;
	}
}
template <class T>
void SeqList::PushBack(const T& data)
{
	CheckCapacity();
	_arr[_size++]=data;
}
void SeqList::PopBack()
{
	if(_size>0)
		_size--;
}
template <class T>
void SeqList::PushFront(const T& data)
{
	CheckCapacity();
	for(int i=_size;i>0;--i)
	{
		_arr[i]=_arr[i-1];
	}
	_arr[0]=data;
	_size++;
}
void  SeqList::PopFront()
{
	if(_size>0)
	{
		for(int i=0;i<_size-1;++i)
		{
			_arr[i]=_arr[i+1];
		}
		--_size;
	}
}
bool SeqList::Find(const T& data)
{
	for(int i=0;i<_size;++i)
	{
		if(_arr[i]==data)
			return true;
	}
	return false;
}
void SeqList::Insert(int pos,const T& data)//任意位置插入
{

	
}
void Erase(int pos);//任意位置删除
int SeqListCapacity();
int SeqListSize();
bool Empty();
T& SeqListFront();//返回第一个元素
T& SeqListBack();//返回最后一个元素
void SeqListRemove(const T& data);//移除第一个为data的元素
void RemoveAll(const T& data);//移除所有为data的元素
void SeqListSort();//排序

