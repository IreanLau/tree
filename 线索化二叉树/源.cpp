

//#include"ThreadBinTree.h"
#include"БъЭЗ.h"
void main()
{
	const char *str = "ABC##DE##F##G#H##";
	BinTree<char> mytree('#');
	mytree.CreateBinTree(str);

	///////////////////////////////////////////////////
	mytree.CreateInThread();

	BinTreeNode<char> *a=mytree.First();
	BinTreeNode<char> *b= mytree.Last();

	
	BinTreeNode<char> *p = mytree.Find('B');
	BinTreeNode<char> *parent = mytree.Parent(p);
}
