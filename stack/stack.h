#pragma once
#include <iostream>
using namespace std;
template <class T>
class Stack
{
	public:
		T* _arr;
		int _top;
		int _capacity;
	public:
		Stack()
			:_arr(nullptr)
			 ,_top(0)
			 ,_capacity(0)
	{
		_arr=new T[3];
		_capacity=3;
	}
		Stack(const Stack& s)
		{
			_capacity=s._capacity;
			_top=s._top;
			_arr=new T[s._capacity];
			for(int i=0;i<_top;++i)
			{
				_arr[i]=s._arr[i];
			}
		}
		Stack& operator=(const Stack& s)
		{
			if(this!=&s)
			{
				swap(_capacity,s._capacity);
				swap(_top,s._top);
				swap(_arr,s._arr);
			}
			return *this;
		}
		void CheckCapacity();
		void StackPush(const T data);
		void StackPop();
		const T& StackTop()const;
		int StackSize();
		bool Empty();
		void StackPrint();
		~Stack()
		{
			if(_arr)
			{
				delete _arr;
				_arr=nullptr;
				_capacity=0;
				_top=0;
			}
		}
};
