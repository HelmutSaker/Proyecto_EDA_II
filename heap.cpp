#include <iostream>
#include "Paciente.h"
using namespace std;

class MaxHeap{
private:
    Paciente * arr;
    int N;
    int last;

public:
    MaxHeap(int n){
        N=n;
        arr = new Paciente[N+1];
        last = 0;
    }

    void insert(Paciente p){
        if(last+1 >= N){
            cout<<"El heap esta lleno"<<endl;
            return;
        }
        last++;
        arr[last]=p;

        int i=last;
        while(i>1 && arr[i].nivelUrg > arr[i/2].nivelUrg){
            swap(arr[i],arr[i/2]);
            i=i/2;
        }
    }

    Paciente extractMax(){
        if (last==0){
            cout << "Heap Vacio" << endl;
            return {-1, "", -1};
        }

        Paciente max = arr[1];
        arr[1] = arr[last--];
        int i  = 1;
        
        while(i*2 <= last){
            int olderSon = i*2;
            if (2*i + 1 <= last && arr[2*i + 1].nivelUrg > arr[2*i].nivelUrg)
                olderSon = 2*i + 1;
            if (arr[i].nivelUrg < arr[olderSon].nivelUrg){
                swap(arr[i], arr[olderSon]);
                i = olderSon;
            }
            else break;
        }
        return max;
    }

    void print(){
        for(int i=1;i<=last;i++)
            cout<< arr[i].idPaciente << " | " << arr[i].nombre << " | " << "Urgencia: " << arr[i].nivelUrg << "\n";
        cout<<endl;
    }
};

