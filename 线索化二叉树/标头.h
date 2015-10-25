#pragma once
#include<iostream>
#include<assert.h>

using namespace std;

typedef enum { LINK, THREAD }Tag_Type;

template<class Ty>
class BinTree;

template<class Ty>
class BinTreeNode
{
	friend class BinTree<Ty>;
	typedef BinTreeNode<Ty>* NodePtr;
public:

	BinTreeNode() :data(Ty()), leftChild(NULL), rightChild(NULL), ltag(LINK), rtag(LINK)
	{}
	BinTreeNode(Ty d,NodePtr L=NULL,NodePtr R=NULL,Tag_Type l=LINK,Tag_Type r=LINK):data(d),leftChild(L),
		rightChild(R),ltag(l),rtag(r)
	{}
	~BinTreeNode()
	{}
	Ty Get()
	{
		return data;
	}
	private:
		Ty data;
		NodePtr leftChild;
		NodePtr rightChild;
		Tag_Type ltag;
		Tag_Type rtag;
};

template<class Ty>
class BinTree
{
	typedef BinTreeNode<Ty>* NodePtr;
public:
	BinTree() :root(NULL)
	{}
	BinTree(Ty ref) :root(NULL), refvalue(ref)
	{}
	~BinTree()
	{}
public:
	void CreateBinTree(const char*str)
	{
		CreateBinTree(root, str);
	}
	void CreateInThread()
	{
		if (root != NULL)
		{
			NodePtr pre = NULL;
			CreateInThread(root, pre);
			pre->rtag = THREAD;
			pre->rightChild = NULL;/*当树建立到最右边，把其线索化*/
		}
	}
public:
	BinTreeNode<Ty>* First()const
	{
		return First(root);
	}
	BinTreeNode<Ty>* Last()const
	{
		return Last(root);
	}
	BinTreeNode<Ty>* Next(BinTreeNode<Ty> *cur)const
	{
		return Next(root, cur);
	}
	BinTreeNode<Ty>* Prio(BinTreeNode<Ty> *cur)const
	{
		return Prio(root, cur);
	}
	void InOrder()const
	{
		InOrder(root);
	}
	BinTreeNode<Ty>* Find(const Ty &key)const
	{
		return Find(root, key);
	}
	BinTreeNode<Ty>*Parent(BinTreeNode<Ty> *cur)const
	{
		return Parent(root, cur);
	}

private:
	NodePtr Parent(NodePtr t, NodePtr cur)const
	{
		if (t == NULL || cur == NULL || cur == t)
			return NULL;
		BinTreeNode<Type> *p;
		if (cur->ltag == THREAD)
		{
			pre = cur->leftChild;
			if (pre->rightChild == cur)
				return pre;
		}
		if (cur->rtag == THREAD)
		{
			pre = cur->rightChild;
			if (pre->leftChild == cur)
				return pre;
		}

		pre = First(cur);
		pre = pre->leftChild;
		if (pre != NULL && pre->rightChild == cur)
			return pre;
		pre = Last(cur);
		return pre->rightChild;

	}
	BinTreeNode<Ty>* Find(BinTreeNode<Ty> *t,
		const Ty &key)const
	{
		BinTreeNode<Ty> *p;
		for (p = First(); p != NULL&&p->data != key; p = Next(p));
		return p;
	}
	void InOrder(BinTreeNode<Ty> *t)const
	{
		BinTreeNode<Ty> *p;
		for (p = First(); p != NULL; p = Next(p))
			cout << p->data << " ";
	}
	BinTreeNode<Ty>* Prio(NodePtr t, BinTreeNode<Ty> *cur)const
	{
		if (t == NULL || cur == NULL)
			return NULL;
		if (cur->ltag == THREAD)
			return cur->leftChild;
		return Last(cur->leftChild);
	}

	BinTreeNode<Ty>* Next(NodePtr t, BinTreeNode<Ty> *cur)const
	{
		if (t == NULL || cur==NULL)
			return NULL;
		if (cur->rtag == THREAD)
			return cur->rightChild;
		return First(cur->rightChild);
	}

	NodePtr Last(NodePtr cur)const
	{
		if (cur == NULL)
			return NULL;
		while (cur->rtag == LINK)
			cur = cur->rightChild;
		return cur;
	}
	NodePtr First(NodePtr cur)const
	{
		if (cur == NULL)
			return NULL;
		while (cur->ltag != THREAD)
			cur = cur->leftChild;
		return cur;
	}
	void CreateInThread(NodePtr&t,
		NodePtr&pre)
	{
		if (t == NULL)
			return;
		CreateInThread(t->leftChild, pre);
		if (t->leftChild == NULL)
		{
			t->ltag = THREAD;
			t->leftChild = pre;
		}
		if (pre != NULL && pre->rightChild == NULL)
		{
			pre->rtag = THREAD;
			pre->rightChild = t;
		}
		pre = t;
		CreateInThread(t->rightChild, pre);
	}
	void CreateBinTree(NodePtr &t, const char *&str)
	{
		if (*str == refvalue)
			t = NULL;
		else
		{
			t = new BinTreeNode<Ty>(*str);
			assert(t != NULL);
			CreateBinTree(t->leftChild, ++str);
			CreateBinTree(t->rightChild, ++str);
		}
	}
private:
	BinTreeNode<Ty>* root;
	Ty refvalue;
};