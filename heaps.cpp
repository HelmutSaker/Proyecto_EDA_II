#include <iostream>
using namespace std;

class MinHeap{
   private:
       static const int TAM = 100;
       int heap[TAM];
       int size;
   public:
       MinHeap(){
           size = 0;
       }
       void insertar(int n){
           if(size+1>=TAM){
               cout<<"El heap está lleno"<<endl;
               return;
           }
           size++;
           heap[size] = n;
           int i = size;
           while(i>1&&heap[i]<heap[i/2]){
               swap(heap[i],heap[i/2]);
               i = i/2;
           }
       }
       void imprimir(){
           for(int i=1;i<=size;i++)
               cout<<heap[i]<<" - ";
           cout<<endl;
       }

       int extraerMin(){
            if (size == 0){
                cout << "Heap vacío" << endl;
                return -1;
            }
            int minimo = heap[1];
            heap[1] = heap[size];
            size--;
            int i = 1;  
            while (2*i <= size){
                int hijoMenor = 2*i;
                if (2*i + 1 <= size && heap[2*i + 1] < heap[2*i])
                    hijoMenor = 2*i + 1;
                if (heap[i] > heap[hijoMenor]){
                    swap(heap[i], heap[hijoMenor]);
                    i = hijoMenor;
                } else {
                    break;
                }
            }
            return minimo;
        }
        bool esMinHeap(){
            for (int i = 1; i <= size / 2; i++){
                if (2*i <= size && heap[i] > heap[2*i])
                    return false;
                if (2*i + 1 <= size && heap[i] > heap[2*i + 1])
                    return false;
            }
            return true;
        }



        void reestructurarMinHeap(int i){
            int hijoIzq = 2 * i;
            int hijoDer = 2 * i + 1;
            int menor = i;
            if (hijoIzq <= size && heap[hijoIzq] < heap[menor]){
                menor = hijoIzq;
            }   
            if (hijoDer <= size && heap[hijoDer] < heap[menor]){
                menor = hijoDer;
            }
            if (menor != i){
                swap(heap[i], heap[menor]);
                reestructurarMinHeap(menor);  
            }
        }




};


int main() {
    MinHeap heapcito;
    heapcito.insertar(20);
    heapcito.insertar(5);
    heapcito.insertar(15);
    heapcito.insertar(22);
    heapcito.insertar(10);
    heapcito.insertar(30);
    heapcito.insertar(3);
    heapcito.imprimir();
  


   return 0;
}