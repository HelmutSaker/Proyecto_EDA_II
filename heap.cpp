#include <iostream>
using namespace std;

class MinHeap{
private:
    int * arr;
    int N;
    int last;
public:
    MinHeap(int n){
        N=n;
        arr = new int[N];
        last = 0;
    }
    void insert(int n){
        if(last+1>=N){
            cout<<"El heap está lleno"<<endl;
            return;
        }
        last++;
        arr[last]=n;
        int i=last;
        while(i>1&&arr[i]<arr[i/2]){
            swap(arr[i],arr[i/2]);
            i=i/2;
        }
    }
    void print(){
        for(int i=0;i<=last;i++)
            cout<<arr[i]<<" - ";
        cout<<endl;
    }
};

int main()
{
    MinHeap heapcito(50);
    heapcito.insert(10);
    heapcito.insert(9);
    heapcito.insert(8);
    heapcito.insert(7);
    heapcito.insert(6);
    heapcito.insert(5);
    heapcito.insert(4);
    heapcito.insert(3);
    heapcito.insert(2);
    heapcito.print();
    return 0;
}
