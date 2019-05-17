#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <cstdlib>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
using namespace std;
/* Head ends here */
typedef struct node
{
    int val;
    struct node* left;
    struct node* right;
    int ht;
    int childCnt;
} node;

node* justInsert(node* root,node* nd);
int getFactor(node* root);
int isBalance(node* root);
int height(node* root);
int fixHeight(node* root);
node* fixTree(node* root,node* proot,int isleft);
node* LR(node* root,node* proot,int isleft);
node* RR(node* root,node* proot,int isleft);
node* LL(node* root,node* proot,int isleft);
node* RL(node* root,node* proot,int isleft);
void deleteNode(node** root,int data);
node** getNextMinNode(node** root);
node** getPreMaxNode(node** root);
int isLeaf(node* root);
int fixChildCount(node* root);
int getMid(node* root);
node** getNode(node** root,int data);
node * insert(node * root,int val)
{
    node* nd = new node;
    nd->val = val;
    nd->left = 0;
    nd->right = 0;
    nd->ht = 0;
    root = justInsert(root,nd);
    fixHeight(root);
    node* rt = fixTree(root,0,false);
    fixHeight(rt);
    return rt;
    
}

node* justInsert(node* root,node* nd)
{
    if (root == 0) {
        return nd;
    }
    node* cd = root;
    node* tg = 0;
    int isleft = 0;
    while (cd) {
        int val = nd->val;
        if (val < cd->val) {
            tg = cd;
            isleft = 1;
            cd = cd->left;
        }else if(val > cd->val) {
            tg = cd;
            isleft = 0;
            cd = cd->right;
        }else {
            delete nd;
            return root;
        }
    }
    if (isleft == 1) {
        tg->left = nd;
    }else {
        tg->right = nd;
    }
    return root;
}


int getFactor(node* root)
{
    if (!root) return 0;
    int fac = height(root->left) - height(root->right);
    return fac;
}

int isBalance(node* root){
    if (!root) {
        return 1;
    }
    int fac = getFactor(root);
    if (fac >= -1 && fac <= 1) {
        return 1;
    }
    return 0;
}

int height(node* root)
{
    if (root==0){
        return -1;
    }else {
        return root->ht;
    }
    
}

node* fixTree(node* root,node* proot,int isleft)
{
    if (!isBalance(root->left)) {
        root->left = fixTree(root->left,root,1);
        return root;
    }else if(!isBalance(root->right)) {
        root->right = fixTree(root->right,root,0);
        return root;
    }else if(!isBalance(root)){
        
        
        if (getFactor(root) == 2 && getFactor(root->left) == -1) {
            //LR
            LR(root,proot,isleft);
            return LL(root,proot,isleft);
        }else if(getFactor(root) == 2 && getFactor(root->left) == 1) {
            //LL
            return LL(root,proot,isleft);
        }else if(getFactor(root) == -2 && getFactor(root->right)== 1 ) {
            //RL
            RL(root,proot,isleft);
            return RR(root,proot,isleft);
        }else if(getFactor(root) == -2 && getFactor(root->right) == -1) {
            //RR
            return RR(root,proot,isleft);
        }
    }
    return root;
}

int fixHeight(node* root)
{
    if (root == 0) {
        return -1;
    }else {
        int lt = fixHeight(root->left);
        int rt = fixHeight(root->right);
        root->ht = lt > rt ? lt + 1: rt + 1;
        return root->ht;
    }
}

int fixChildCount(node* root)
{
    if (root == 0) {
        return 0;
    }else {
        int lt = fixChildCount(root->left);
        int rt = fixChildCount(root->right);
        root->childCnt = lt + rt;
        return root->childCnt + 1;
    }
}


node* LR(node* root,node* proot,int isleft){
    node* l = root->left;
    node* lr = l->right;
    root->left = lr;
    l->right = lr->left;
    lr->left = l;
    return root;
}

node* LL(node* root,node* proot,int isleft){
    node* l = root->left;
    node* ll = l->left;
    
    root->left = l->right;
    l->right = root;
    if (proot) {
        if (isleft) {
            proot->left = l;
        }else {
            proot->right = l;
        }
    }
    
    return l;
    
}

node* RL(node* root,node* proot,int isleft){
    node* r = root->right;
    node* rl = r->left;
    root->right = rl;
    r->left = rl->right;
    rl->right = r;
    return root;
}

node* RR(node* root,node* proot,int isleft){
    node* r = root->right;
    node* rr = r->right;
    
    root->right = r->left;
    r->left = root;
    if (proot) {
        if (isleft) {
            proot->left = r;
        }else {
            proot->right = r;
        }
    }
    return r;
}

void deleteNode(node** root,int data)
{
    node** target = getNode(root,data);
    if (!target) {
        return;
    }
    if ((*target)->left && (*target)->right) {
        node** re = getNextMinNode(target);
        (*target)->val = (*re)->val;
        deleteNode(re,(*re)->val);
    }else if ((*target)->left) {
        if (isLeaf((*target)->left)) {
            (*target)->val = (*target)->left->val;
            deleteNode(&((*target)->left),(*target)->left->val);
        }else {
            node** re = getPreMaxNode(&((*target)->left));
            (*target)->val = (*re)->val;
            deleteNode(re,(*re)->val);
        }
        
    }else if ((*target)->right) {
        if (isLeaf((*target)->right)) {
            (*target)->val = (*target)->right->val;
            deleteNode(&((*target)->right),(*target)->right->val);
        }else {
            node** re = getNextMinNode(&((*target)->right));
            (*target)->val = (*re)->val;
            deleteNode(re,(*re)->val);
        }
    }else {
        delete (*target);
        *target = 0;
    }
}

int isLeaf(node* root)
{
    return (!root->left&&!root->right);
}
node** getNode(node** root,int data)
{
    if (!(*root)) return 0;
    node** cr = root;
    while(*cr) {
        if ((*cr)->val < data) {
            cr = &((*cr)->right);
        }else if((*cr)->val > data) {
            cr = &((*cr)->left);
        }else {
            return cr;
        }
    }
    return 0;
}

node** getNextMinNode(node** root)
{
    if (!(*root)) {
        return 0;
    }
    node** cr = &((*root)->right);
    while(*cr) {
        if ((*cr)->left) {
            cr = &((*cr)->left);
        }else {
            return cr;
        }
    }
    return 0;
}

node** getPreMaxNode(node** root)
{
    if (!(*root)) {
        return 0;
    }
    node** cr = &((*root)->left);
    while(*cr) {
        if ((*cr)->right) {
            cr = &((*cr)->right);
        }else {
            return cr;
        }
    }
    return 0;
}

int getMid(node* root){
    fixChildCount(root);
    if (!root) {
        std::cout<<"Wrong!"<<std::endl;
    }else {
        int lc = 0;
        int rc = 0;
        if (root->left) {
            lc = root->left->childCnt + 1;
        }
        if (root->right) {
            rc = root->right->childCnt + 1;
        }
        if ((root->childCnt + 1) % 2 == 0) {
            
            if (lc > rc) {
                std::cout<<(root->val + (*getPreMaxNode(&root))->val)/2.0<<std::endl;
            } else if (lc < rc){
                std::cout<<(root->val + (*getNextMinNode(&root))->val)/2.0<<std::endl;
            }
        }else {
            if (lc > rc) {
                std::cout<<(*getPreMaxNode(&root))->val<<std::endl;
            } else if (lc < rc){
                std::cout<< (*getNextMinNode(&root))->val<<std::endl;
            } else {
                std::cout<<root->val<<std::endl;
            }
            
        }
    }
    return 0;
}

void opera(node** root,char op,int data)
{
	if (op == 'r') {
		deleteNode(root,data);
	}else if(op == 'a') {
		*root = insert(*root,data);
	}
}

void median(vector<char> s,vector<int> X) {
   node* root = 0;
   for (int i = 0; i < s.size(); i++)
   {
   		opera(&root,s[i],X[i]);
   		getMid(root);
   }
    
}
int main(void){

//Helpers for input and output

	int N;
	cin >> N;
	
	vector<char> s;
    vector<int> X;
	char temp;
    int tempint;
	for(int i = 0; i < N; i++){
		cin >> temp >> tempint;
        s.push_back(temp);
        X.push_back(tempint);
	}
	
	median(s,X);
	return 0;
}
