#include "SeqList.h"
template <class T>
void SeqList<T>:: show()//打印
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
template <class T>
void SeqList<T>::CheckCapacity()
{
	if(_size==_Capacity)
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
void SeqList<T>::PushBack(const T& data)
{
	CheckCapacity();
	_arr[_size++]=data;
}
template <class T>
void SeqList<T>::PopBack()
{
	if(_size>0)
		_size--;
}
template <class T>
void SeqList<T>::PushFront(const T& data)
{
	CheckCapacity();
	for(int i=_size;i>0;--i)
	{
		_arr[i]=_arr[i-1];
	}
	_arr[0]=data;
	_size++;
}
template <class T>
void SeqList<T>::PopFront()
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
template <class T>
int SeqList<T>::Find(const T& data)
{
	for(int i=0;i<_size;++i)
	{
		if(_arr[i]==data)
			return i;
	}
	return -1;
}
template <class T>
void SeqList<T>::Insert(int pos,const T& data)//任意位置插入
{
	if(pos<0 || pos>_size)
	{
		cout<<"插入位置不合法"<<endl;
		return;
	}
	CheckCapacity();
	for(int i=_size-1;i>=pos;--i)
	{
		_arr[i+1]=_arr[i];
	}
	_arr[pos]=data;
	_size++;
}
template <class T>
void SeqList<T>::Erase(int pos)//任意位置删除
{
	if(pos<0 || pos>=_size)
	{
		cout<<"删除位置不合法"<<endl;
		return;
	}
	for(int i=pos;i<_size;++i)
	{
		_arr[i]=_arr[i+1];
	}
	_size--;
}
template <class T>
int SeqList<T>::SeqListCapacity()
{
	return _Capacity;
}
template <class T>
int SeqList<T>::SeqListSize()
{
	return _size;
}
template <class T>
bool SeqList<T>::Empty()
{
	return 0==_size;
}
template <class T>
T& SeqList<T>::SeqListFront()//返回第一个元素
{
	return _arr[0];
}
template <class T>
T& SeqList<T>::SeqListBack()//返回最后一个元素
{
	return _arr[_size-1];
}
template <class T>
void SeqList<T>::SeqListRemove(const T& data)//移除第一个为data的元素
{
	Erase(Find(data));
}
template <class T>
void SeqList<T>::RemoveAll(const T& data)//移除所有为data的元素
{
	int count=0;
	for(int i=0;i<_size;++i)
	{
		if(_arr[i]==data)
		{
			count++;
		}
		else
		{
			_arr[i-count]=_arr[i];
		}
	}
	_size-=count;
}
template <class T>
void SeqList<T>::SeqListSort()//排序
{
	for(int i=0;i<_size-1;++i)
	{
		int flag=0;
		for(int j=0;j<_size-1-i;++j)
		{
			if(_arr[j]>_arr[j+1])
			{
				swap(_arr[j],_arr[j+1]);
				flag=1;
			}
		}
		if(flag==0)
			break;
	}
}

