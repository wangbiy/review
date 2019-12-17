#include "BinTree.h"
template <class T>
void BinTree<T>::_PreOrder(BTNode<T>* pRoot)
{
	if(_pRoot==nullptr)
		return;
	cout<<pRoot->_data<<" ";
	_PreOrder(pRoot->_pLeft);
	_PreOrder(pRoot->_pRight);
}
template <class T>
void BinTree<T>::PreOrder()
{
	_PreOrder(_pRoot);
	cout<<endl;
}
template <class T>
void BinTree<T>::_InOrder(BTNode<T>* pRoot)
{
	if(pRoot==nullptr)
		return;
	_InOrder(pRoot->_pLeft);
	cout<<pRoot->_data<<"";
	_InOrder(pRoot->_pRight);
}
template <class T>
void BinTree<T>::InOrder()
{
	_InOrder(_pRoot);
	cout<<endl;
}
template <class T>
void BinTree<T>::_PostOrder(BTNode<T>* pRoot)
{
	if(pRoot==nullptr)
		return;
	_PostOrder(pRoot->_pLeft);
	_PostOrder(pRoot->_pRight);
	cout<<pRoot->_data<<"";
}
template <class T>
void BinTree<T>::PostOrder()
{
	_PostOrder(_pRoot);
	cout<<endl;
}
#include <stack>
template <class T>
void BinTree<T>::PreOrderNor()
{
	BTNode<T>* pCur=_pRoot;
	stack<BTNode<T>*> st;
	while(pCur!=nullptr || !st.empty())
	{
		while(pCur!=nullptr)
		{
			cout<<pCur->_data<<" ";
			st.push(pCur);
			pCur=pCur->_pLeft;
		}
		BTNode<T>* top=st.top();
		st.pop();
		pCur=top->_pRight;
	}
}
template <class T>
void BinTree<T>::InOrderNor()
{
	BTNode<T>* pCur=_pRoot;
	stack<BTNode<T>*> st;
	while(pCur!=nullptr || !st.empty())
	{
		while(pCur!=nullptr)
		{
			st.push(pCur);
			pCur=pCur->_pLeft;
		}
		BTNode<T>* top=st.top();
		cout<<top->_data<<" ";
		st.pop();
		pCur=top->_pRight;
	}
}
template <class T>
void BinTree<T>::PostOrderNor()
{
	BTNode<T>* pCur=_pRoot;
	BTNode<T>* last=nullptr;//标记左右子树都遍历过的结点
	stack<BTNode<T>*> st;
	while(pCur!=nullptr || !st.empty())
	{
		while(pCur!=nullptr)
		{
			//让最左外层的先全部入栈
			st.push(pCur);
			pCur=pCur->_pLeft;
		}
		BTNode<T>* top=st.top();
		if(top->_pRight==nullptr || top->_pRight==last)
		{
			st.pop();
			cout<<top->_data<<" ";
			last=top;
		}
		else
		{
			pCur=top->_pRight;
		}
	}
}
#include <queue>
template <class T>
void BinTree<T>::LevelOrder()
{
	if(_pRoot==nullptr)
		return;
	queue<BTNode<T>*> q;
	//先让根结点入队，第一个打印根结点
	q.push(_pRoot);
	while(!q.empty())
	{
		BTNode<T>* front=q.front();
		cout<<front->_data<<" ";
		q.pop();
		if(front->_pLeft!=nullptr)
		{
			q.push(front->_pLeft);
		}
		if(front->_pRight!=nullptr)
		{
			q.push(front->_pRight);
		}
	}
}
template <class T>
int BinTree<T>::_GetNodeCount(BTNode<T>* pRoot)
{
	if(pRoot==nullptr)
		return 0;
	int left=_GetNodeCount(pRoot->_pLeft);
	int right=_GetNodeCount(pRoot->_pRight);
	return left+right+1;
}
template <class T>
int BinTree<T>::GetNodeCount()
{
	return _GetNodeCount(_pRoot);
}
template <class T>
int BinTree<T>::_Height(BTNode<T>* pRoot)
{
	if(pRoot==nullptr)
		return 0;
	int left=_Height(pRoot->_pLeft);
	int right=_Height(pRoot->_pRight);
	return max(left,right)+1;
}
template <class T>
int BinTree<T>::Height()
{
	return _Height(_pRoot);
}
template <class T>
int BinTree<T>::_GetLeafCount(BTNode<T>* pRoot)
{
	if(pRoot==nullptr)
		return 0;
	else if(pRoot->_pLeft==nullptr && pRoot->_pRight==nullptr)
		return 1;
	else
	{
		return _GetLeafCount(pRoot->_pLeft)+_GetLeafCount(pRoot->_pRight);
	}
}
template <class T>
int BinTree<T>::GetLeafCount()
{
	return _GetLeafCount(_pRoot);
}
#include <stdlib.h>
template <class T>
bool BinTree<T>::_IsBalanceTree(BTNode<T>* pRoot)
{
	if(pRoot==nullptr)
		return true;
	int h1=_Height(pRoot->_pLeft);
	int h2=_Height(pRoot->_pRight);
	int d=abs(h1-h2);
	return (d<=1)&&(_IsBalanceTree(pRoot->_pLeft)&&_IsBalanceTree(pRoot->_pRight));
}
template <class T>
bool BinTree<T>::IsBalanceTree()
{
	return _IsBalanceTree(_pRoot);
}
template <class T>
bool BinTree<T>::_IsBalanceTree_p(BTNode<T>* pRoot,int* height)
{
	if(pRoot==nullptr)
		return true;
	int leftHeight=_Height(pRoot->_pLeft);
	int rightHeight=_Height(pRoot->_pRight);
	int IsLbalance=_IsBalanceTree_p(pRoot->_pLeft,&leftHeight);
	int IsRbalance=_IsBalanceTree_p(pRoot->_pRight,&rightHeight);
	if(IsLbalance && IsRbalance && abs(rightHeight-leftHeight)<2)
	{
		*height=leftHeight<rightHeight ? leftHeight+1 : rightHeight+1;
		return true;
	}
	return false;
}
template <class T>
bool BinTree<T>::IsBalanceTree_p()
{
	int height=0;
	return _IsBalanceTree_p(_pRoot,&height);
}
#include <assert.h>
template <class T>
int BinTree<T>::_GetKLevelNodeCount(BTNode<T>* pRoot,int k)
{
	assert(k>=1);
	if(pRoot==nullptr)
		return 0;
	if(k==1)
		return 1;
	else
	{
		_GetKLevelNodeCount(pRoot->_pLeft,k-1)+_GetKLevelNodeCount(pRoot->_pRight,k-1);
	}
}
template <class T>
int BinTree<T>::GetKLevelNodeCount(int k)
{
	return _GetKLevelNodeCount(_pRoot,k);
}
template <class T>
BTNode<T>* BinTree<T>::_Find(BTNode<T>* pRoot,T v)
{
	if(pRoot==nullptr)
		return nullptr;
	else if(pRoot->_data==v)
		return pRoot;
	else
	{
		BTNode<T>* left=_Find(pRoot->_pLeft,v);
		if(left!=nullptr)
			return left;
		return _Find(pRoot->_pRight,v);
	}
}
template <class T>
BTNode<T>* BinTree<T>::Find(T v)
{
	return _Find(_pRoot,v);
}
template <class T>
BTNode<T>* BinTree<T>::_GetNodeParent(BTNode<T>* pRoot,BTNode<T>* Node)
{
	BTNode<T>* pParent=nullptr;
	if(pRoot==nullptr || Node==nullptr)
		return nullptr;
	if(pRoot==Node)
		return nullptr;
	if(pRoot->_pLeft==Node || pRoot->_pRight==Node)
		return pRoot;
	pParent=_GetNodeParent(pRoot->_pLeft,Node);
	if(pParent!=nullptr)
		return pParent;
	return _GetNodeParent(pRoot->_pRight,Node);
}
template <class T>
BTNode<T>* BinTree<T>::GetNodeParent(BTNode<T>* Node)//获取二叉树中某个节点的双亲节点
{
	return _GetNodeParent(_pRoot,Node);
}
template <class T>
bool BinTree<T>::_Mirror(BTNode<T>* s,BTNode<T>* t)
{
	if(s==nullptr && t==nullptr)
		return true;
	if(s==nullptr || t==nullptr)
		return false;
	return (s->_data == t->_data) && _Mirror(s->_pLeft,t->_pRight)&&_Mirror(s->_pRight,t->_pLeft);
}
template <class T> 
bool BinTree<T>::Mirror(BTNode<T>* root)
{
	return _Mirror(_pRoot,root); 
}
template <class T>
bool BinTree<T>::_isCompleteTree(BTNode<T>* pRoot)
{
	if(pRoot==nullptr)
		return true;
	queue<BTNode<T>*> q;
	q.push(pRoot);
	while(true)
	{
		BTNode<T>* front=q.front();
		q.pop();
		if(front==nullptr)
			break;
		q.push(front->_pLeft);
		q.push(front->_pRight);
	}
	while(!q.empty())
	{
		BTNode<T>* front=q.front();
		q.pop();
		if(front!=nullptr)
			return false;
	}
	return true;
}
template <class T>
bool BinTree<T>::isCompleteTree()
{
	return _isCompleteTree(_pRoot);
}

