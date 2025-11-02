#include "hash.cpp"
#include "heap.cpp"
#include "Paciente.h"
#include <iostream>
using namespace std;

int main(){
    TablaHash tabla(20);
    MaxHeap heap(20);

    Paciente p1 = {1, "Jose", 4};
    Paciente p2 = {2, "Luis", 2};
    Paciente p3 = {3, "Cesar", 5};

    tabla.insertar(p1);
    tabla.insertar(p2);
    tabla.insertar(p3);

    heap.insert(p1);
    heap.insert(p2);
    heap.insert(p3);

    cout << "TABLA HASH:\n";
    tabla.imprimir();

    cout << "HEAP (URGENCIA):\n";
    heap.print();

    Paciente atendido = heap.extractMax();
    cout << "Atendido: " << atendido.nombre << " Urgencia: " << atendido.nivelUrg << "\n";

    return 0;
}
