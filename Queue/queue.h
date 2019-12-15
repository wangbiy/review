#pragma once
#include <iostream>
using namespace std;
template <class T>
class QNode
{
	public:
		QNode* _pNext;
		T _data;
		QNode(const T data)
			:_pNext(nullptr)
			 ,_data(data)
	{}
};
template <class T>
class Queue
{
	public:
		QNode<T>* _front;
		QNode<T>* _rear;
	public:
		Queue()
			:_front(nullptr)
			 ,_rear(nullptr)
	{}
		void QueuePush(const T data);
		void QueuePop();
		const T& QueueFront()const;
		const T& QueueBack()const;
		bool Empty()const;
		int QueueSize()const;
		void QueuePrint();
		~Queue()
		{
			QNode<T>* pCur=_front;
			while(pCur)
			{
				_front=pCur->_pNext;
				delete pCur;
				pCur=_front;
			}
			_front=_rear=nullptr;
		}
		
};
