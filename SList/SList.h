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
	Node(T data)
		:_data(data)
		 ,_pNext(nullptr)
	{}
};
template <class T>
class SList
{
	public:
		SList()
			:_pHead(nullptr)
		{}
		SList(const SList& l)
			:_pHead(nullptr)
		{
			Node<T>* pCur=l._pHead;
			if(pCur==nullptr)
				return;
			while(pCur)
			{
				this->PushBack(pCur->_data);
				pCur=pCur->_pNext;
			}
		}
		SList& operator=(const SList& s)
		{
			if(this!=&s)
			{
				swap(_pHead,s._pHead);
			}
			return *this;
		}
		void SListPushBack(T data);
		void SListPopBack();
		void SListPushFront(T data);
		void SListPopFront();
		void SListInsertAfter(Node<T>* pos,T data);
		void SListErase(Node<T>* pos);
		Node<T>* SListFind(const T data);
		int SListSize();//返回结点个数
		T SListFront();
		T SListBack();
		bool SListEmpty();
		void PrintSList();
		Node<T>* ReverseSList();
		~SList()
		{
			DestroySList();
		}
	private:
		void DestroySList()
		{
			Node<T>* pCur=_pHead;
			while(pCur)
			{
				Node<T>* pDelNode=pCur;
				pCur=pCur->_pNext;
				delete pDelNode;
			}
			_pHead=nullptr;
		}
	public:
			Node<T>* _pHead;
};
