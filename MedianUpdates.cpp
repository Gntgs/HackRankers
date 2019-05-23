#include "AVLTree/AVLTree.h"
#include "AVLTree/TreeUtils.h"
using namespace std;

void median(vector<char> s,vector<int> X) {
    Tree::AVLTree<int> tree_min;
    Tree::AVLTree<int> tree_max;
    ios::fmtflags f(cout.flags());
    for (int i = 0; i < s.size(); i++)
    {
        bool succ = true;
        if (s[i] == 'a') {
            tree_max.Insert(X[i]);
            if (tree_min.GetSize() > 0) {
                if (tree_max.GetMin() < tree_min.GetMax()) {
                    int m = tree_max.GetMin();
                    tree_min.Insert(m);
                    tree_max.Remove(m);
                }
            }
        }else if(s[i] == 'r') {
            succ = tree_max.Remove(X[i]);
            if (!succ) {
                succ = tree_min.Remove(X[i]);
            }
        }

        if (tree_max.GetSize() - tree_min.GetSize() >= 2) {
            //move max min to min max
            int m = tree_max.GetMin();
            tree_min.Insert(m);
            tree_max.Remove(m);
        }else if (tree_max.GetSize() - tree_min.GetSize() <= -2) {
            int m = tree_min.GetMax();
            tree_min.Remove(m);
            tree_max.Insert(m);
        }

        int cnt = tree_min.GetSize() + tree_max.GetSize();
        if (cnt <= 0 || !succ){
            std::cout.flags(f);
            std::cout<<"Wrong!"<<std::endl;
        }else {
            if (tree_min.GetSize() ==  tree_max.GetSize()) {
                double res = ((double)tree_min.GetMax() + tree_max.GetMin())/2.0;
                if ( int(res) == res) {
                    printf("%.lf\n",res);
                }else {
                    printf("%0.1lf\n",res);
                }
                
            }else {
                double res = tree_min.GetSize() > tree_max.GetSize() ? tree_min.GetMax() : tree_max.GetMin();
                printf("%0.lf\n",res);
            }
        }
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
         //cin >> temp >> tempint;
     		temp = 'a';
     		tempint = i;
            s.push_back(temp);
            X.push_back(tempint);
     }
    
    median(s,X);
    return 0;
}
