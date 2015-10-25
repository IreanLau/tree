#pragma once

#include<iostream>
#include<assert.h>
using namespace std;

typedef enum { LINK, THREAD }Tag_Type;

template<class Type>
class BinTree;

template<class Type>
class BinTreeNode
{
	friend class BinTree<Type>;
public:
	BinTreeNode() :data(Type()), leftChild(NULL), rightChild(NULL), ltag(LINK), rtag(LINK)
	{}
	BinTreeNode(Type d, BinTreeNode<Type>*left = NULL, BinTreeNode<Type>*right = NULL)
		:data(d), leftChild(left), rightChild(right), ltag(LINK), rtag(LINK)
	{}
	~BinTreeNode()
	{}
private:
	Type data;
	BinTreeNode<Type> *leftChild;
	BinTreeNode<Type> *rightChild;
	Tag_Type ltag;
	Tag_Type rtag;
};

template<class Type>
class BinTree
{
public:
	BinTree() :root(NULL)
	{}
	BinTree(Type ref) :root(NULL), refvalue(ref)
	{}
public:
	void CreateBinTree(const char *str)
	{
		CreateBinTree(root, str);
	}
	void CreateInThread()
	{
		if (root != NULL)
		{
			BinTreeNode<Type> *pre = NULL;
			CreateInThread(root, pre);
			pre->rtag = THREAD;
			pre->rightChild = NULL;
		}
	}
public:
	BinTreeNode<Type>* First()const
	{
		return First(root);
	}
	BinTreeNode<Type>* Last()const
	{
		return Last(root);
	}
	BinTreeNode<Type>* Next(BinTreeNode<Type> *cur)const
	{
		return Next(root, cur);
	}
	BinTreeNode<Type>* Prio(BinTreeNode<Type> *cur)const
	{
		return Prio(root, cur);
	}
	void InOrder()const
	{
		InOrder(root);
	}
	BinTreeNode<Type>* Find(const Type &key)const
	{
		return Find(root, key);
	}
	BinTreeNode<Type>*Parent(BinTreeNode<Type> *cur)const
	{
		return Parent(root, cur);
	}
private:

	BinTreeNode<Type>*Parent(BinTreeNode<Type> *t,
		BinTreeNode<Type> *cur)const
	{
		if (t == NULL || cur == NULL || cur == t)
			return NULL;
		BinTreeNode<Type> *p;
		if (cur->ltag == THREAD)
		{
			p = cur->leftChild;
			if (p->rightChild == cur)
				return p;
		}
		if (cur->rtag == THREAD)
		{
			p = cur->rightChild;
			if (p->leftChild == cur)
				return p;
		}
		p = First(cur);
		p = p->leftChild;
		if (p != NULL && p->rightChild == cur)
			return p;
		p = Last(cur);
		return p->rightChild;
	}

	/*
	BinTreeNode<Type>*Parent(BinTreeNode<Type> *t,
	BinTreeNode<Type> *cur)const
	{
	if(t==NULL)
	return t;
	BinTreeNode<Type>* p=Next(cur);
	while(p!=NULL && (p->leftChild!=cur || p->ltag!=LINK))
	p=Next(p);
	if(p==NULL)
	{
	p=Prio(cur);
	while(p!=NULL && (p->rightChild!=cur || p->rtag!=LINK))
	p=Prio(p);
	}
	return p;
	}
	*/
	BinTreeNode<Type>* Find(BinTreeNode<Type> *t,
		const Type &key)const
	{
		BinTreeNode<Type> *p;
		for (p = First(); p != NULL&&p->data != key; p = Next(p));
		return p;
	}
	void InOrder(BinTreeNode<Type> *t)const
	{
		BinTreeNode<Type> *p;
		for (p = First(); p != NULL; p = Next(p))
			cout << p->data << " ";
	}
	BinTreeNode<Type>* Prio(BinTreeNode<Type>*t, BinTreeNode<Type> *cur)const
	{
		if (t == NULL || cur == NULL)
			return NULL;
		if (cur->ltag == THREAD)
			return cur->leftChild;
		return Last(cur->leftChild);
	}
	BinTreeNode<Type>* Next(BinTreeNode<Type>*t, BinTreeNode<Type> *cur)const
	{
		if (t == NULL || cur == NULL)
			return NULL;
		if (cur->rtag == THREAD)
			return cur->rightChild;
		return First(cur->rightChild);
	}
	BinTreeNode<Type>* Last(BinTreeNode<Type> *cur)const
	{
		if (cur == NULL)
			return NULL;
		while (cur->rtag == LINK)
			cur = cur->rightChild;
		return cur;
	}
	BinTreeNode<Type>* First(BinTreeNode<Type> *cur)const
	{
		if (cur == NULL)
			return NULL;
		while (cur->ltag == LINK)
			cur = cur->leftChild;
		return cur;
	}
	void CreateInThread(BinTreeNode<Type>*&t,
		BinTreeNode<Type> *&pre)
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

	void CreateBinTree(BinTreeNode<Type> *&t, const char *&str)
	{
		if (*str == refvalue)
			t = NULL;
		else
		{
			t = new BinTreeNode<Type>(*str);
			assert(t != NULL);
			CreateBinTree(t->leftChild, ++str);
			CreateBinTree(t->rightChild, ++str);
		}
	}
private:
	BinTreeNode<Type> *root;
	Type               refvalue;
}; 