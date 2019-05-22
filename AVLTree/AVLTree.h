#ifndef __AVLTREE_H__
#define __AVLTREE_H__
#include <vector>
namespace Tree{
	template<class T>
	class AVLTree{
		friend class TreeUtils;
	public:
		AVLTree();
		void Insert(T data);
		bool Remove(T data);
		int  GetSize();
		T    GetMax();
		T    GetMin();
	protected:
		struct Node{
			int height;
			T data;
			Node* left;
			Node* right;
		};
		Node* Insert(Node* root,Node* nd);
		Node* Remove(Node* root,Node* nd);
		Node* GetNode(T data);
		Node* CreateNode(T data);
		//void  EraseNode(Node* node);
		Node* RR(Node* root);
		Node* RL(Node* root);
		Node* LL(Node* root);
		Node* LR(Node* root);
		Node* GetRoot();
		Node* GetPreMaxNode(Node* root);
		Node* GetNextMinNode(Node* root);
	private:
		Node* root;
		bool  isDel;
		int   size;
	};
	
	template<class T>
	AVLTree<T>::AVLTree(){
        root  = NULL;
        size  = 0;
        isDel = false;
	}
	template<class T>
	typename AVLTree<T>::Node* AVLTree<T>::GetRoot()
	{
		return root;
	}
	
	template<class T>
	void AVLTree<T>::Insert(T data)
	{
		Node* nd = CreateNode(data);
		root = Insert(root,nd);
		size += 1;
	}

	template<class T>
	T  AVLTree<T>::GetMax(){
		if (!root) {
			return NULL;
		}

		Node* rt = root;
		while(rt->right) {
			rt = rt->right;
		}
		return rt->data;
	}

	template<class T>
	T  AVLTree<T>::GetMin(){
		if (!root) {
			return NULL;
		}

		Node* rt = root;
		while(rt->left) {
			rt = rt->left;
		}
		return rt->data;
	}

	template<class T>
	int  AVLTree<T>::GetSize()
	{
		return size;
	}


	template<class T>
	typename AVLTree<T>::Node* AVLTree<T>::CreateNode(T data)
	{
		Node* nd = new Node;
		nd->height = 0;
		nd->left   = NULL;
		nd->right  = NULL;
		nd->data   = data;
		return nd;
	}
	
	#define HEIGHT(nd) ((nd) == NULL ? -1 : (nd)->height)
	#define MAX(a,b) ((a) > (b) ? (a) : (b))
	#define CPNODE(dst,src) ((dst)->data = (src)->data)
	
	template<class T>
	typename AVLTree<T>::Node* AVLTree<T>::Insert(Node* root,Node* nd)
	{
		if (!root) {
			return nd;
		}
		
		if (root->data < nd->data) {
			root->right = Insert(root->right,nd);
			if (HEIGHT(root->right) - HEIGHT(root->left) == 2) {
				if (nd->data < root->right->data) {
					return RL(root);
				}else {
					return RR(root);
				}
			}
		}else if (root->data >= nd->data) {
			root->left = Insert(root->left,nd);
			if (HEIGHT(root->left) - HEIGHT(root->right) == 2) {
				if (nd->data > root->left->data) {
					return LR(root);
				}else {
					return LL(root);
				}
			}
		}
		root->height = MAX( HEIGHT(root->left), HEIGHT(root->right)) + 1;
		return root;
	}
	
	template<class T>
	typename AVLTree<T>::Node* AVLTree<T>::RR(Node* root)
	{
		Node* r = root->right;
	    Node* rr = r->right;
	    
	    root->right = r->left;
	    r->left = root;
	
	    root->height = MAX(HEIGHT(root->left),HEIGHT(root->right)) + 1;
	    r->height = MAX(HEIGHT(root),HEIGHT(rr)) + 1;
	    return r;
	}
	
	template<class T>
	typename AVLTree<T>::Node* AVLTree<T>::RL(Node* root)
	{
		root->right = LL(root->right);
	    return RR(root);
	}
	
	template<class T>
	typename AVLTree<T>::Node* AVLTree<T>::LL(Node* root)
	{
		Node* l = root->left;
	    Node* ll = l->left;
	    
	    root->left = l->right;
	    l->right = root;
	
	    root->height = MAX(HEIGHT(root->left),HEIGHT(root->right)) + 1;
	    l->height = MAX(HEIGHT(root),HEIGHT(ll)) + 1;
	
	    return l;
	}
	
	template<class T>
	typename AVLTree<T>::Node* AVLTree<T>::LR(Node* root)
	{
		root->left = RR(root->left);
		return LL(root);
	}
	
	template<class T>
	typename AVLTree<T>::Node* AVLTree<T>::GetPreMaxNode(Node* root)
	{
		if (!root) {
			return NULL;
		}
		Node* nd = root->left;
		while(nd) {
			if (nd->right) {
				nd = nd->right;
			}else {
				break;
			}
		}
		return nd;
	}
	
	
	template<class T>
	typename AVLTree<T>::Node* AVLTree<T>::GetNextMinNode(Node* root)
	{
	
		if (!root) {
			return NULL;
		}
		Node* nd = root->right;
		while(nd) {
			if (nd->left) {
				nd = nd->left;
			}else {
				break;
			}
		}
		return nd;
	}
	
	
	template<class T>
	typename AVLTree<T>::Node* AVLTree<T>::GetNode(T data)
	{
		Node* cr = root;
		while (cr) {
			if (cr->data < data) {
				cr = cr->right;
			}else if (cr->data > data) {
				cr = cr->left;
			}else {
				return cr;
			}
		}
		return NULL;
	}
	
	#define ISLEAF(nd) !((nd)->left)&&!((nd)->right)
	template<class T>
	bool AVLTree<T>::Remove(T data)
	{
		Node tg;
		tg.data = data;
		isDel = true;
		root = Remove(root,&tg);
		if (isDel) {
			size-=1;
		}
		return isDel; 
	}
	
	template<class T>
	typename AVLTree<T>::Node* AVLTree<T>::Remove(Node* root,Node* target)
	{
		if (!root) {
			isDel = false;
			return NULL;
		}
	
		if (root->data < target->data) {
			root->right = Remove(root->right,target);
			if (HEIGHT(root->left) - HEIGHT(root->right) == 2) {
				Node* l = root->left;
				if (HEIGHT(l->left) > HEIGHT(l->right)) {
					//LL
					return LL(root);
				}else {
					return LR(root);
				}
			}
		}else if (root->data > target->data) {
			root->left = Remove(root->left,target);
			if (HEIGHT(root->right) - HEIGHT(root->left) == 2 ) {
				Node* r = root->right;
				if (HEIGHT(r->left) > HEIGHT(r->right)) {
					return RL(root);
				}else {
					return RR(root);
				}
			}
		}else {
			if (root->left && root->right) {
				if (HEIGHT(root->left) > HEIGHT(root->right)) {
					Node* re = GetPreMaxNode(root);
					CPNODE(root,re);
					root->left = Remove(root->left,re);
				}else {
					Node* re = GetNextMinNode(root);
					CPNODE(root,re);
					root->right = Remove(root->right,re);
				}
			}else {
                Node* nd = root;
                root = root->left?root->left:root->right;
                delete nd;
			}
		}
        if (root)
        root->height = MAX( HEIGHT(root->left), HEIGHT(root->right)) + 1;
		return root;
	}

}

#endif
