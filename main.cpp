#include "hash.cpp"
#include "heap.cpp"
#include "Paciente.h"
#include <iostream>
using namespace std;

int main(){
    Hash tablaHash;
    MaxHeap heap(20);

    Paciente p1 = {1, "Jose", 4};
    Paciente p2 = {2, "Luis", 2};
    Paciente p3 = {3, "Cesar", 5};

    tablaHash.insert(p1);
    tablaHash.insert(p2);
    tablaHash.insert(p3);

    heap.insert(p1);
    heap.insert(p2);
    heap.insert(p3);

    cout << "TABLA HASH:\n";
    tablaHash.print();

    cout << "HEAP (URGENCIA):\n";
    heap.print();

    Paciente atendido = heap.extractMax();
    cout << "Atendido: " << atendido.nombre << " Urgencia: " << atendido.nivelUrg << "\n";

    return 0;
}
