#pragma once
#include <iostream>
using namespace std;
#include <stdlib.h>
template <class T>
class Node
{
	public:
		T _data;
		Node* _pNext;
		Node* _pPre;
		Node(const T& data)
			:_data(data)
			 ,_pNext(nullptr)
			 ,_pPre(nullptr)
	{}
};
template <class T>
class DList
{
	public:
		Node<T>* _pHead;
	public:
	DList()	
		:_pHead(nullptr)
	{
		_pHead=new Node<T>(0);//创建头结点
		_pHead->_pNext=_pHead;
		_pHead->_pPre=_pHead;
	}
	DList(const DList& d)
	{
		_pHead=new Node<T>(0);
		_pHead->_pNext=_pHead;
		_pHead->_pPre=_pHead;
		Node<T>* pCur=d._pHead->_pNext;
		while(pCur!=d._pHead)
		{
			this->DListPushBack(pCur->_data);
			pCur=pCur->_pNext;
		}
	}
	DList& operator=(const DList& d)
	{
		if(this!=&d)
		{
			swap(_pHead,d._pHead);
		}
		return *this;
	}
	void DListPushBack(const T data);
	void DListPopBack();
	void DListPushFront(const T data);
	void DListPopFront();
	void DListInsert(Node<T>* pos,const T data);
	void DListErase(Node<T>* pos);
	Node<T>* Find(const T data);
	void PrintDList();
	void DListClear();//将有效结点清理
	int DListSize();
	bool Empty();
	const T& DListFront()const;
	const T& DListBack()const;
	~DList()
	{
		DListClear();
		delete _pHead;
		_pHead=nullptr;
	}
};
