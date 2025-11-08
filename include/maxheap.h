#pragma once
#include <iostream>
#include <tuple>
#include "Paciente.h"
#include "hash.h"
using namespace std;

class MaxHeap{
private:
    tuple<int, int>* arr;
    int N;
    int last;

public:
    MaxHeap(int n){
        N=n;
        arr = new tuple<int, int>[N+1];
        last = 0;
    }

    ~MaxHeap(){
        delete[] arr;
    }

    int getSize()
    {return last;}

    void insert(int urgencia, int index){
        if(last+1 >= N){
            cout<<"El heap esta lleno"<<endl;
            return;
        }
        last++;
        arr[last]=make_tuple(urgencia, index);

        int i=last;
        while(i>1 && get<0>(arr[i]) > get<0>(arr[i/2])){
            swap(arr[i],arr[i/2]);
            i=i/2;
        }
    }

    tuple<int,int> extractMax(){
        if (last==0){
            cout << "Heap Vacio" << endl;
            return {-1, -1};
        }

        tuple<int, int> max = arr[1];
        arr[1] = arr[last];
        last--;

        int i  = 1;
        while(i*2 <= last){
            int olderSon = i*2;
            if (2*i + 1 <= last && get<0>(arr[2*i + 1]) > get<0>(arr[2*i]))
                olderSon = 2 * i + 1;
            if (get<0>(arr[i]) < get<0>(arr[olderSon])){
                swap(arr[i], arr[olderSon]);
                i = olderSon;
            }
            else break;
        }
        return max;
    }

    void print(){
        for(int i=1;i<=last;i++)
            cout<< "Urgencia: " << get<0>(arr[i]) 
            << " | Indice Hash: " << get<1>(arr[i]) << "\n";
        cout<<endl;
    }
};