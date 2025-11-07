#pragma once
#include <iostream>
#include "Paciente.h"
using namespace std;

class Hash {
public:
    Paciente* tabla;
    bool* ocupado;
    int SIZE;
    int numElementos;

    Hash(int size = 10007) {  // Tamaño primo para mejor distribución
        SIZE = size;
        tabla = new Paciente[SIZE];
        ocupado = new bool[SIZE];
        for (int i = 0; i < SIZE; i++)
            ocupado[i] = false;
        numElementos = 0;
    }

    ~Hash(){
        delete[] ocupado;
        delete[] tabla;
    }

    int hashFunction(int id){
        return id % SIZE;
    }

    void insert(Paciente p){
        if (numElementos >= SIZE) {
            cout << "Tabla hash llena" << endl;
            return;
        }
        
        int index = hashFunction(p.getId());
        int temp = index;

        while(ocupado[index]){
            // Si el paciente ya existe, actualizamos
            if (tabla[index].getId() == p.getId()){
                tabla[index] = p;
                return;
            }
            index = (index + 1) % SIZE;
            if (index == temp){
                cout << "Tabla llena" << endl;
                return;
            }
        }

        tabla[index] = p;
        ocupado[index] = true;
        numElementos++;
    }

    Paciente* buscarPaciente(int id){
        int pos = hashFunction(id);
        int temp = pos;

        while (ocupado[pos]){
            if (tabla[pos].getId() == id){
                return &tabla[pos];
            }
            pos = (pos + 1) % SIZE;
            if (pos == temp) break;
        }
        return nullptr; 
    }

    void mostrarPaciente(int id){
        Paciente* p = buscarPaciente(id);
        if (p != nullptr){
            cout << "Paciente encontrado:\n";
            cout << "ID: " << p->getId() << " | Nombre: " << p->getNombre()
                 << " | Urgencia: " << p->getUrgencia() << endl;
            
            // Mostrar estado
            string estado = "En espera";
            if (p->getAtendido()) estado = "Atendido";
            if (p->getConCita()) estado = " con cita programada";
            
            cout << "Estado: " << estado << endl;
        } else {
            cout << "Paciente no encontrado" << endl;
        }
    }

    void print(){
        int count = 0;
        for(int i = 0; i < SIZE && count < numElementos; i++){
            if (ocupado[i]){
                cout << i << " --> ID: " << tabla[i].getId()
                     << " | Nombre: " << tabla[i].getNombre()
                     << " | Urgencia: " << tabla[i].getUrgencia() << endl;
                count++;
            }
        }
        cout << "Total pacientes: " << numElementos << endl;
    }
};