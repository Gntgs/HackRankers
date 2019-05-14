#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

void moveArray(int* array,int type,int s, int e,int arrayLen){
	int *cacheArray = new int[e-s+1];
	memcpy(cacheArray,array+s-1,sizeof(int)*(e-s+1));
	if (type == 1) {
		for (int i = 0; i < s; i++) {
			array[e - i - 1] = array[s - i - 2];
		}
		for (int i = 0; i < e - s + 1; i++) {
			array[i] = cacheArray[i];
		}
	}else {
		for (int i = s - 1; i < arrayLen - (e - s + 1); i++) {
			array[i] = array[i + (e - s + 1)];
		}
		int j = 0;
		for (int i = arrayLen - (e - s + 1),j = 0; i < arrayLen; i++,j++) {
			array[i] = cacheArray[j];
		}
	}
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */  
    int arrayLen,queryCount;
    cin >> arrayLen >> queryCount;
    int* array = new int[arrayLen]; 
    for (int i = 0; i < arrayLen; i++) {
    	cin >> array[i];
    }
    int type;
    int s,e;
    for (int i = 0; i < queryCount; i++) {
    	cin >> type >> s >> e;
    	moveArray(array,type,s,e,arrayLen);
    }
    cout << abs(array[0] - array[arrayLen-1])<<endl;
    for (int i = 0; i < arrayLen; i++) {
    	cout << array[i] << " ";
    }
    return 0;
}
