#pragma once
#include <iostream>
using namespace std;
template <class T>
class BTNode
{
	public:
		BTNode<T>* _pLeft;
		BTNode<T>* _pRight;
		T _data;
		BTNode(const T data)
			:_pLeft(nullptr)
			 ,_pRight(nullptr)
			 ,_data(data)
	{}
};
template <class T>
class BinTree
{
	public:
		BinTree(T* array,size_t size)//构造函数
		{
			size_t index=0;
			_CreateBinTree(array,size,index);
		}
		BinTree(const BinTree<T>& t)//拷贝构造函数
		{
			_pRoot=CopyBinTree(t._pRoot);
		}
		BinTree<T>& operator=(const BinTree<T>& t)
		{
			if(this!=&t)
			{
				swap(_pRoot,t._pRoot);
			}
			return *this;
		}
		BTNode<T>* CopyBinTree(BTNode<T>* pRoot)//二叉树的拷贝
		{
			if(pRoot==nullptr)
				return nullptr;
			BTNode<T>* pNewRoot=new BTNode<T>(pRoot->_data);
			pNewRoot->_pLeft=CopyBinTree(pRoot->_pLeft);
			pNewRoot->_pRight=CopyBinTree(pRoot->_pRight);
			return pNewRoot;
		}
		void _PreOrder(BTNode<T>* pRoot);
		void _InOrder(BTNode<T>* pRoot);
		void _PostOrder(BTNode<T>* pRoot);
		void PreOrder();
		void InOrder();
		void PostOrder();
		void PreOrderNor();
		void InOrderNor();
		void PostOrderNor();
		void LevelOrder();
		int _GetNodeCount1(BTNode<T>* pRoot);
		int GetNodeCount1();
		int _GetNodeCount2(BTNode<T>* pRoot);
		int GetNodeCount2();
		int _Height(BTNode<T>* pRoot);
		int Height();
		int _GetLeafCount(BTNode<T>* pRoot);
		int GetLeafCount();
		bool _IsBalanceTree(BTNode<T>* pRoot);
		bool IsBalanceTree();
		bool _IsBalanceTree_p(BTNode<T>* pRoot,int* height);
		bool IsBalanceTree_p();
		int _GetKLevelNodeCount(BTNode<T>* pRoot,int k);
		int GetKLevelNodeCount(int k);
		BTNode<T>* _Find(BTNode<T>* pRoot,const T v);
		BTNode<T>* Find(const T v);
		BTNode<T>* _GetNodeParent(BTNode<T>* pRoot,BTNode<T>* Node);
		BTNode<T>* GetNodeParent(BTNode<T>* Node);//获取二叉树中某个节点的双亲节点
		bool Mirror(BTNode<T>* root);
		bool _Mirror(BTNode<T>* s,BTNode<T>* t);
		bool _isCompleteTree(BTNode<T>* pRoot);
		bool isCompleteTree();
		~BinTree()
		{
			DestroyBinTree(_pRoot);
			_pRoot=nullptr;
		}
	public:
		void DestroyBinTree(BTNode<T>* pRoot)
		{
			if(pRoot==nullptr)
				return;
			DestroyBinTree(pRoot->_pLeft);
			DestroyBinTree(pRoot->_pRight);
			delete pRoot;
		}
		BTNode<T>* _CreateBinTree(const T* array,size_t size,size_t& index)
		{
			BTNode<T>* pRoot=nullptr;
			if(index<size && array[index]!='#')
			{
				pRoot=new BTNode<T>(array[index]);
				index++;
				pRoot->_pLeft=_CreateBinTree(array,size,index);
				index++;
				pRoot->_pRight=_CreateBinTree(array,size,index);
			}
			return pRoot;
		}
	public:
		BTNode<T>* _pRoot;
};
