#include "DList.h"
#include <assert.h>
template <class T>
void DList<T>::DListPushBack(const T data)
{
	Node<T>* pNewNode=new Node<T>(data);
	pNewNode->_pPre=_pHead->_pPre;
	pNewNode->_pNext=_pHead;
	_pHead->_pPre=pNewNode;
	pNewNode->_pPre->_pNext=pNewNode;
}
template <class T>
void DList<T>::DListPopBack()
{
	assert(_pHead);
	if(_pHead==_pHead->_pNext)
		return;
	else
	{
		Node<T>* pDelNode=_pHead->_pPre;
		pDelNode->_pPre->_pNext=_pHead;
		_pHead->_pPre=pDelNode->_pPre;
		delete pDelNode;
	}
}
template <class T>
void DList<T>::DListPushFront(const T data)
{
	Node<T>* pNewNode=new Node<T>(data);
	pNewNode->_pNext=_pHead->_pNext;
	pNewNode->_pPre=_pHead;
	_pHead->_pNext=pNewNode;
	pNewNode->_pNext->_pPre=pNewNode;
}
template <class T>
void DList<T>::DListPopFront()
{
	assert(_pHead);
	if(_pHead==_pHead->_pNext)
		return;
	else
	{
		Node<T>* pDelNode=_pHead->_pNext;
		_pHead->_pNext=pDelNode->_pNext;
		pDelNode->_pNext->_pPre=_pHead;
		delete pDelNode;
	}
}
template <class T>
void DList<T>::DListInsert(Node<T>* pos,const T data)//插入到pos前面
{
	Node<T>* pNewNode=new Node<T>(data);
	if(pos==nullptr)
		return;
	else
	{
		pNewNode->_pNext=pos;
		pNewNode->_pPre=pos->_pPre;
		pos->_pPre=pNewNode;
		pNewNode->_pPre->_pNext=pNewNode;
	}
}
template <class T>
void DList<T>::DListErase(Node<T>* pos)
{
	assert(_pHead);
	if(pos==nullptr)
		return;
	pos->_pPre->_pNext=pos->_pNext;
	pos->_pNext->_pPre=pos->_pPre;
	delete pos;
}
template <class T>
Node<T>* DList<T>::Find(const T data)
{
	assert(_pHead);
	Node<T>* pCur=_pHead->_pNext;
	while(pCur!=_pHead)
	{
		if(pCur->_data==data)
			return pCur;
		pCur=pCur->_pNext;
	}
	return nullptr;
}
template <class T>
void DList<T>::PrintDList()
{
	Node<T>* pCur=_pHead->_pNext;
	while(pCur!=_pHead)
	{
		cout<<pCur->_data<<" ";
		pCur=pCur->_pNext;
	}
	cout<<endl;
}
template <class T>
void DList<T>::DListClear()//将有效结点清理
{
	Node<T>* pCur=_pHead->_pNext;
	while(pCur!=_pHead)
	{
		_pHead->_pNext=pCur->_pNext;
		delete pCur;
		pCur=_pHead->_pNext;
	}
	_pHead->_pNext=_pHead;
	_pHead->_pPre=_pHead;

}
template <class T>
int DList<T>::DListSize()
{
	Node<T>* pCur=_pHead->_pNext;
	int size=0;
	while(pCur!=_pHead)
	{
		size++;
		pCur=pCur->_pNext;
	}
	return size;
}
template <class T>
bool DList<T>::Empty()
{
	return _pHead->_pNext==_pHead ? true:false;
}
template <class T>
const T& DList<T>::DListFront()const
{
	assert(_pHead);
	return _pHead->_pNext->_data;
}
template <class T>
const T& DList<T>::DListBack()const
{
	assert(_pHead);
	return _pHead->_pPre->_data;
}
