//
//  main.cpp
//  AVL
//
//  Created by 苟爽 on 2019/5/10.
//  Copyright © 2019 苟爽. All rights reserved.
//

#include <iostream>
typedef struct node
{
    int val;
    struct node* left;
    struct node* right;
    int ht;
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

int main(int argc, const char * argv[]) {
    node* root = 0;
    root = insert(root,3);
    root = insert(root,2);
    root = insert(root,4);
    root = insert(root,5);
    root = insert(root,6);
    return 0;
}
