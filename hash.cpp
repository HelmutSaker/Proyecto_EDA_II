#include <iostream>
#include "Paciente.h"
using namespace std;

class Hash{
private:
    Paciente** tabla;
    int SIZE = 10;
    int numElementos;

public:
    Hash(){
        tabla = new Paciente*[SIZE];
        for(int i=0;i<SIZE;i++)
            tabla[i] = nullptr;

        numElementos = 0;
    }

    ~Hash(){
        for(int i=0; i<SIZE; i++){
            delete tabla[i];
        }
        delete[] tabla;
    }

    int hashFunction(int id){
        return id % SIZE;
    }

    void insert(Paciente p){
        int index = hashFunction(p.idPaciente);
        int temp = index;

        while(tabla[index] != nullptr){
            index = (index + 1) % SIZE;
            if (index == temp){
                cout << "Tabla llena" << endl;
                return;
            }
        }

        tabla[index] = new Paciente(p);
        numElementos++;
    }

    void search(int id){
        int pos = hashFunction(id);
        int temp = pos;

        while (tabla[pos] != nullptr){
            if (tabla[pos]->idPaciente == id){
                cout << "Paciente encontrado:\n";
                cout << pos << " --> ID: " << tabla[pos]->idPaciente << " | Nombre: " << tabla[pos]->nombre << " | Urgencia: " << tabla[pos]->nivelUrg << endl;
                return;
            }
            pos = (pos + 1) % SIZE;
            if (pos == temp) break;
        }
        cout << "Paciente no encontrado" << endl; 
        
    }
    void print(){
        for(int i=0;i<SIZE;i++)
            if (tabla[i] != nullptr){
                cout << i << " --> ID: " << tabla[i]->idPaciente << " | Nombre: " << tabla[i]->nombre << " | Urgencia: " << tabla[i]->nivelUrg << endl;
            } else {
                cout << i << " --> " << endl;
            }
    }

};

