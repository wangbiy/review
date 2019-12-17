#include "BinTree.hpp"
#include "BinTree.h"
#include <string.h>
void TestBinTree()
{
	char* str="ABD##E#H##CF##G##";
	BinTree<char*> root(str,strlen(str),"#");
	cout<<"创建二叉树成功"<<endl;

	BinTree<char*> pNewTree(root);
	cout<<"拷贝成功"<<endl;
	cout<<"二叉树root的前序排列是:";
	root.PreOrder();
	cout<<endl;
	cout<<"二叉树root的中序排列是:";
	root.InOrder();
	cout<<endl;
	cout<<"二叉树root的后序排列是:";
	root.PostOrder();
	cout<<endl;

	cout<<"二叉树pNewTree的前序排列是:";
	pNewTree.PreOrder();
	cout<<endl;
	cout<<"二叉树pNewTree的中序排列是:";
	pNewTree.InOrder();
	cout<<endl;
	cout<<"二叉树pNewTree的后序排列是:";
	pNewTree.PostOrder();
	cout<<endl;

	cout<<"二叉树pNewTree的前序排列非递归是:";
	pNewTree.PreOrderNor();
	cout<<endl;
	cout<<"二叉树pNewTree的中序排列非递归是:";
	pNewTree.InOrderNor();
	cout<<endl;
	cout<<"二叉树pNewTree的后序排列非递归是:";
	pNewTree.PostOrderNor();
	cout<<endl;

	cout<<"二叉树root的层序遍历是:";
	root.LevelOrder();
	cout<<endl;

	int size=root.GetNodeCount();
	cout<<"结点个数是:"<<size<<endl;

	int height=root.Height();
	cout<<"二叉树的高度是:"<<height<<endl;

	size=root.GetLeafCount();
	cout<<"叶子结点个数是:"<<size<<endl;

	bool ret=root.IsBalanceTree();
	if(ret==true)
		cout<<"是平衡二叉树!"<<endl;
	if(ret==false)
		cout<<"不是平衡二叉树!"<<endl;

	ret=pNewTree.IsBalanceTree_p();
	if(ret==true)
		cout<<"是平衡二叉树!"<<endl;
	if(ret==false)
		cout<<"不是平衡二叉树!"<<endl;
	size=root.GetKLevelNodeCount(3);
	cout<<"获取第三层的结点个数是:"<<size<<endl;

	//BTNode<char*>* pParent=root.GetNodeParent(root.Find('F'));
	//char str1[] = "ACG##F##BEH###D##";
	//BinTree<char*> t(str1,sizeof(str1)/sizeof(str1[0]),'#');
//	ret=root.Mirror(t);
//	if(ret==true)
//		cout<<"root与t互为镜像"<<endl;
//	if(ret==false)
//		cout<<"root与t不为镜像"<<endl;
//
	ret=root.isCompleteTree();
	if(ret==true)
		cout<<"root是完全二叉树"<<endl;
	if(ret==false)
		cout<<"root不是完全二叉树"<<endl;
}
int main()
{
	TestBinTree();
	return 0;
}
