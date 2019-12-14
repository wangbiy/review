#include "SList.h"
template <class T>
void SList<T>::SListPushBack(T data)
{
	if(_pHead==nullptr)//直接插入
	{
		_pHead=new Node<T>(data);
	}
	else
	{
		Node<T>* pCur=_pHead;
		while(pCur->_pNext)
		{
			pCur=pCur->_pNext;
		}
		pCur->_pNext=new Node<T>(data);
	}
}
template <class T>
void SList<T>::SListPopBack()
{
	if(_pHead==nullptr)
		return;
	else if(_pHead->_pNext==nullptr)//只有第一个结点
	{
		delete _pHead;
		_pHead=nullptr;
	}
	else
	{
		Node<T>* pPreNode=nullptr;
		Node<T>* pTailNode=_pHead;
		while(pTailNode->_pNext)
		{
			pPreNode=pTailNode;
			pTailNode=pTailNode->_pNext;
		}
		delete pTailNode;
		pPreNode->_pNext=nullptr;
	}
}
template <class T>
void SList<T>::SListPushFront(T data)
{
	Node<T>* pNewNode=new Node<T>(data);
	pNewNode->_pNext=_pHead;
	_pHead=pNewNode;
}
template <class T>
void SList<T>::SListPopFront()
{
	if(_pHead==nullptr)
		return;
	else
	{
		Node<T>* pDelNode=_pHead;
		_pHead=pDelNode->_pNext;
		delete pDelNode;
	}
}
template <class T>
void SList<T>::SListInsertAfter(Node<T>* pos,T data)
{
	if(pos==nullptr)
		return;
	else
	{
		Node<T>* pNewNode=new Node<T>(data);
		pNewNode->_pNext=pos->_pNext;
		pos->_pNext=pNewNode;
	}
}
template <class T>
void SList<T>::SListErase(Node<T>* pos)
{
	if(_pHead==nullptr || pos==nullptr)
		return;
	if(pos==_pHead)//只有一个结点
	{
		_pHead=pos->_pNext;
		delete pos;
		return;
	}
	Node<T>* pPreNode=_pHead;
	while(pPreNode->_pNext!=pos)
	{
		pPreNode=pPreNode->_pNext;
	}
	pPreNode->_pNext=pos->_pNext;
	delete pos;
}
template <class T>
Node<T>* SList<T>::SListFind(const T data)
{
	Node<T>* pCur=_pHead;
	while(pCur)
	{
		if(pCur->_data==data)
			return pCur;
		else
			pCur=pCur->_pNext;
	}
	return pCur;
}
template <class T>
int SList<T>::SListSize()//返回结点个数
{
	Node<T>* pCur=_pHead;
	int count=0;
	while(pCur)
	{
		pCur=pCur->_pNext;
		count++;
	}
	return count;
}
template <class T>
T SList<T>::SListFront()
{
	return _pHead->_data;
}
template <class T>
T SList<T>::SListBack()
{
	Node<T>* pCur=_pHead;
	while(pCur->_pNext)
	{
		pCur=pCur->_pNext;
	}
	return pCur->_data;
}
template <class T>
bool SList<T>::SListEmpty()
{
	return _pHead==nullptr ? true:false;
}
template <class T>
void SList<T>::PrintSList()
{
	Node<T>* pCur=_pHead;
	while(pCur)
	{
		cout<<pCur->_data<<"--->";
		pCur=pCur->_pNext;
	}
	cout<<"nullptr"<<endl;
}
template <class T>
Node<T>* SList<T>::ReverseSList()
{
	if(_pHead==nullptr || _pHead->_pNext==nullptr)
		return nullptr;
	Node<T>* p=_pHead->_pNext;//先将头结点后的保存一份
	_pHead->_pNext=nullptr;//再将头结点后的置空
	while(p!=nullptr)//将头结点后的结点头插到头结点前，就实现了逆置
	{
		Node<T>* next=p->_pNext;
		p->_pNext=_pHead;
		_pHead=p;
		p=next;
	}
	return _pHead;
}
