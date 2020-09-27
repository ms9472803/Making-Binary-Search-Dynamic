#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <iostream>
#include <vector>
#include <string.h>
#include <math.h>
#include "DynamicBS.h"
using namespace std;
enum operation {opInsert=1, opSearch=2, opDelete=3, opPrint=4, opExit=5};

int BSearch(const int *A, int Size, int key)
{
    int left = 0, right = Size;
    while(left <= right){
        int mid = (left+right)/2;
        if(A[mid]==key){
            return mid;
        }
        else if(A[mid] > key){
            right = mid-1;
        }
        else{
            left = mid+1;
        }
    }
    return -1;
}

void Merge(int *A1, const vector<int>&A2, vector<int> &A3, int arrayIndex)
{
    const int arraySize = pow(2,arrayIndex);
    int i=0,j=0,k=0;

    int a1=A1[0], a2=A2[0];
    while(a1!=0 || a2!=0){
        if(a1!=0 && a1 <= a2 || a2 == 0){
            A3[k] = A1[i];
            i++;
            if(i<arraySize)
                a1 = A1[i];
            else
                a1 = 0;
            k++;
        }
        else if(a2!=0 && a1 > a2 || a1 == 0){
            A3[k] = A2[j];
            j++;
            if(j<arraySize)
                a2 = A2[j];
            else
                a2 = 0;
            k++;
        }

    }
    for(int A1_i=0; A1_i<arraySize; A1_i++){
        A1[A1_i] = 0;
    }
}

void Replace(int *A, int pos, int e, int arrayIndex)
{
    A[pos] = e;
    int arrayLength = pow(2, arrayIndex);
    sort(A, A+arrayLength);
}

DynamicBS::DynamicBS(int defaultSize):size{defaultSize}
{
    
    int k = ceil(log(size+1)/log(2));
    table = new int*[k]; // A_0, A_1, ..., A_k-1
    for(int i=0; i<k; i++){
        const int len = pow(2, i);
        table[i] = new int[len];
    }
    TableInit();
}

DynamicBS::~DynamicBS()
{
    int k = ceil(log(size+1)/log(2));
    for(int i=0; i<k; i++)
        delete [] table[i];
    delete [] table;
}

void DynamicBS::TableInit()
{
    int k = ceil(log(size+1)/log(2));
    for(int i=0; i<k; i++){
        for(int j=0; j<pow(2,i); j++){
            table[i][j] = 0;
        }
    }
}

void DynamicBS::Print()const
{
    int k = ceil(log(numElement+1)/log(2));
    for(int i=0; i<k; i++){
        for(int j=0; j<pow(2,i); j++){
            cout << table[i][j] << ' ';
        }
        cout << endl;
    }
}

vector<int> DynamicBS::Search(int key)const
{
    vector<int> result;
    int i = 0;
    int n = numElement;
    while(n > 0){
        if(n%2 == 1){
            int pos = BSearch(table[i], pow(2,i), key);
            if(pos != -1){
                //cout << i << ' ' << pos << endl;
                result = {i, pos};
                return result;
            }
        }
        n = n/2;
        i = i+1;
    }
    //cout << key << " not found" << endl;
    return result;
}

void DynamicBS::Insert(int element)
{
    if(numElement+1>size){
        cout << "table full" << endl;
        return;
    }

    int n = numElement;
    int k = ceil(log(n+1)/log(2));

    vector<vector<int>> B = {{element}}; //B_0 = {e}
    int i=0;
    while(n%2!=0){
        vector<int> tmp(pow(2,i+1)); //Generate B_i+1 array of size 2^{i+1}
        B.push_back(tmp);
        Merge(table[i], B[i], B[i+1], i);
        n = n/2;
        i = i+1;
    }

    for(int j=0; j<pow(2,i); j++){ //A_i = B_i
        table[i][j] = B[i][j];
    }
    numElement++;
}

void DynamicBS::Delete(int target)
{

    vector<int> searchResult = Search(target);
    if(searchResult.size() == 0){
        cout << "not found" << endl;
        return;
    }

    int arrayIndex = searchResult[0], pos = searchResult[1];

    int n = numElement;
    int k = 0;
    while(n%2==0){
        n = n/2;
        k = k+1;
    }

    if(arrayIndex==k){
        int tmp = pow(2,arrayIndex)-1;
        tmp = tmp==pos?pos-1:tmp;
        Replace(table[arrayIndex],pos,table[arrayIndex][tmp], arrayIndex);
    }
    else{ // i > k
        int tmp = pow(2,k)-1;
        Replace(table[arrayIndex], pos, table[k][tmp], arrayIndex);
    }

    int i=0;
    for(i=0; i<k; i++){
        int tmp = 0;
        for(int j=pow(2,i)-1; j<pow(2,i+1)-1; j++,tmp++){
            table[i][tmp] = table[k][j];
        }
    }

    for(int j=0; j<pow(2,i); j++){
        table[i][j] = 0;
    }
    numElement--;
}

void DynamicBS::OpI()
{
    operation op;
    do{
        cout << "Dynamic Binary Search Operation:\n";
        cout << "(1) Insert\n";
        cout << "(2) Search\n";
        cout << "(3) Delete\n";
        cout << "(4) Print\n";
        cout << "(5) Exit\n";
        cout << "Input a operation...>";
        int inputOp = 0;
        cin >> inputOp;
        op = static_cast<operation>(inputOp);
        switch(op){
            case opInsert:
                {
                    if(numElement>=size){
                        cout << "Cannot Insert\n";
                        break;
                    }
                    cout << "\n***Insert***\n" ;
                    cout << "Input a number...>";
                    int number = 0;
                    cin >> number;
                    Insert(number);
                }
            break;
            case opSearch:
                {
                    cout << "\n***Search***\n" ;
                    cout << "Input a number...>";
                    int key = 0;
                    cin >> key;
                    vector<int> arr;
                    arr = Search(key);
                    if(arr.size()!=0)
                        cout << key << ": " << "[" << arr[0] << "]" << "[" << arr[1] << "]" << endl;
                    else
                        cout << key << " not found" << endl;
                }
            break;
            case opDelete:
                {
                    cout << "\n***Delete***\n" ;
                    cout << "Input a number...>";
                    int target = 0;
                    cin >> target;
                    Delete(target);
                }
            break;
            case opPrint:
                {
                    int Size = ceil(log(numElement+1)/log(2));
                    Print();
                }
            break;
            default:
                {
                    if(op != opExit)
                        cout << "Invalid operation\n";
                }
            break;
        }
        system("pause");
        //system("cls");
    }while(op!=opExit);
}


