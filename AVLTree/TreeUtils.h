#include "AVLTree.h"
#include <stack>
#include <iostream>
namespace Tree{
	#define ABS(x) (x) < 0 ? (0-(x)) : (x)
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

		template<class T>
		static void GetMidian(AVLTree<T>& tree)
		{
			typedef typename AVLTree<T>::Node* PNode;
			int size = tree.GetSize();
			PNode t1,t2;
			int    tc1,tc2;
			int even = 0;
			if (size%2 == 0) {
				even = 1;
				tc1 = size / 2 - 1;
				tc2 = tc1 + 1;
			}else {
				even = 0;
				tc1 = size / 2;
			}
			int cr = 0;	
			PNode nd = tree.GetRoot();
			std::stack<PNode> s_tack;
			while(!s_tack.empty()||nd) {
                while(nd){
                    s_tack.push(nd);
                    nd = nd->left;
                }
                
                if (!s_tack.empty()) {
                    nd = s_tack.top();
                    if ( even == 1 ) {
                    	if (cr == tc1) {
                    		t1 = nd;
                    	}else if (cr == tc2) {
                    		t2 = nd;
                    		break;
                    	}
                    }else {
                    	if (cr == tc1) {
                    		t1 = nd;
                    		break;
                    	}
                    }
                    //std::cout<<nd->data<<" ";
                    s_tack.pop();
                    cr++;
                    nd = nd->right;
                }
			}

			if (even == 1) {
				long long res = (long long)t1->data + t2->data;
				if (res % 2 != 0) {
					std::cout.precision(1);
					std::cout<< std::fixed << (res)/2.0 <<std::endl;
				}else {
					std::cout.precision(0);
					std::cout<< std::fixed << (res)/2.0 << std::endl;
				}
				
			}else {
				std::cout.precision(0);
				std::cout<< std::fixed << t1->data << std::endl;
			}
		}
	};

}
