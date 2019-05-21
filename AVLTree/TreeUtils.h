#include "AVLTree.h"
#include <stack>
#include <iostream>
namespace Tree{
	class TreeUtils {
	public:
		template<class T>
		static void middleOutPutTree(AVLTree<T>& tree)
		{
			typedef typename AVLTree<T>::Node* PNode;
			PNode nd = tree.GetRoot();
			std::stack<PNode> s_tack;
			while(!s_tack.empty()||nd) {
                while(nd){
                    s_tack.push(nd);
                    nd = nd->left;
                }
                
                if (!s_tack.empty()) {
                    nd = s_tack.top();
                    std::cout<<nd->data<<" ";
                    s_tack.pop();
                    nd = nd->right;
                }
               
			}
		}
	};

}
