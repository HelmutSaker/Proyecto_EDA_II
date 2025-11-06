#pragma once

#include <iostream>
#include "Paciente.h"
using namespace std;

class Hash {
public:
    Paciente* tabla;
    bool* ocupado;
    int SIZE = 10;
    int numElementos;

    Hash() {
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
        int index = hashFunction(p.idPaciente);
        int temp = index;

        while(ocupado[index]){
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

    void buscarPaciente(int id){
        int pos = hashFunction(id);
        int temp = pos;

        while (ocupado[pos]){
            if (tabla[pos].idPaciente == id){
                cout << "Paciente encontrado:\n";
                cout << pos << " --> ID: " << tabla[pos].idPaciente << " | Nombre: " << tabla[pos].nombre << " | Urgencia: " << tabla[pos].nivelUrgencia << endl;
                return;
            }
            pos = (pos + 1) % SIZE;
            if (pos == temp) break;
        }
        cout << "Paciente no encontrado" << endl; 
    }

    void print(){
        for(int i=0;i<SIZE;i++)
            if (ocupado[i]){
                cout << i << " --> ID: " << tabla[i].idPaciente << " | Nombre: " << tabla[i].nombre << " | Urgencia: " << tabla[i].nivelUrgencia << endl;
            } else {
                cout << i << " --> " << endl;
            }
    }
};