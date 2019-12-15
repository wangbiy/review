#include "queue.h"
template <class T>
//队列是用单链表的思想来实现的，由于先进先出，因此是尾插，头删
void Queue<T>::QueuePush(const T data)
{
	QNode<T>* pNewNode=new QNode<T>(data);
	if(nullptr==_rear)
	{
		_rear=_front=pNewNode;
	}
	else
	{
		_rear->_pNext=pNewNode;
		_rear=pNewNode;
	}
}
template <class T>
void Queue<T>::QueuePop()
{
	if(nullptr==_front)
		return;
	else if(_front==_rear)
	{
		delete _front;
		_front=_rear=nullptr;
	}
	else
	{
		QNode<T>* pDelNode=_front;
		_front=pDelNode->_pNext;
		delete pDelNode;
	}
}
template <class T>
const T& Queue<T>::QueueFront()const
{
	return _front->_data;
}
template <class T>
const T& Queue<T>::QueueBack()const
{
	return _rear->_data;
}
template <class T>
bool Queue<T>::Empty()const
{
	return nullptr==_front ? true:false;
}
template <class T>
int Queue<T>::QueueSize()const
{
	QNode<T>* pCur=_front;
	int size=0;
	while(pCur)
	{
		size++;
		pCur=pCur->_pNext;
	}
	return size;
}
template <class T>
void Queue<T>::QueuePrint()
{
	QNode<T>* pCur=_front;
	while(pCur)
	{
		cout<<pCur->_data<<" ";
		pCur=pCur->_pNext;
	}
	cout<<endl;
}
