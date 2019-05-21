#include "AVLTree.h"
#include "TreeUtils.h"
#include <map>
int main()
{
	std::map<int,int> m;
	Tree::AVLTree<int> tree;
	tree.Insert(1);
	tree.Insert(2);
	tree.Insert(3);
	tree.Insert(4);
	tree.Insert(5);
	tree.Insert(6);
	tree.Insert(7);
	tree.Insert(8);
    tree.Remove(4);
    tree.Remove(1);
    tree.Remove(1);
	Tree::TreeUtils::middleOutPutTree(tree);
	return 0;
}
