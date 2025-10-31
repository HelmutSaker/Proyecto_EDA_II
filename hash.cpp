#include <iostream>
#include "Paciente.h"
using namespace std;

class Hash{
private:
    Paciente* tabla;
    bool* ocupado;
    int SIZE = 10;
    int numElementos;

public:
    Hash(){
        tabla = new Paciente[SIZE];
        ocupado = new bool[SIZE];

        for(int i=0;i<SIZE;i++)
            ocupado[i] = false;
    }

    int hashFunction(int id){
        return id%SIZE;
    }
    void insert(Paciente p){
        int index = hashFunction(p.idPaciente);
        int tmp = index;
        while(ocupado[index]){
           index = (index+1)%SIZE;
            if(index==tmp){
                cout<<"La tabla esta llena"<<endl;
                return;
            }
        }
        tabla[index] = p;
        ocupado[index] = true;
        numElementos++;
    }
    void print(){
        for(int i=0;i<SIZE;i++)
            if (ocupado[i]){
                cout << i << " --> ID: " << tabla[i].idPaciente << " | Nombre: " << tabla[i].nombre << " | Urgencia: " << tabla[i].nivelUrg << endl;
            } else {
                cout << i << " --> " << endl;
            }
    }

};

