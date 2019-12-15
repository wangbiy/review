#include "stack.h"
#include <string.h>
template <class T>
void Stack<T>::CheckCapacity()
{
	if(_capacity==_top)
	{
		int newcapacity=_capacity*2;
		T* temp=new T[newcapacity];
		memcpy(temp,_arr,_top*sizeof(_arr[0]));
		delete _arr;
		_arr=temp;
		_capacity=newcapacity;
	}
}
template <class T>
void Stack<T>::StackPush(const T data)
{
	CheckCapacity();
	_arr[_top++]=data;
}
template <class T>
void Stack<T>::StackPop()
{
	if(_top==0)
		return;
	_top--;
}
template <class T>
const T& Stack<T>::StackTop()const
{
	return _arr[_top-1];
}
template <class T>
int Stack<T>::StackSize()
{
	return _top;
}
template <class T>
bool Stack<T>::Empty()
{
	return 0==_top ? true:false;
}
template <class T>
void Stack<T>::StackPrint()
{
	for(int i=_top;i>0;--i)
	{
		cout<<_arr[i-1]<<" ";
	}
	cout<<endl;
}
