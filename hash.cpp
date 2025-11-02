#include <iostream>
#include "Paciente.h"
using namespace std;

class TablaHash{
private:
    Paciente* tabla;
    bool* ocupado;
    int tam;
    int colisiones;
    int elementos;

public:
    TablaHash(int t) {
        tam = t;
        tabla = new Paciente[tam];
        ocupado = new bool[tam];
        colisiones = 0;
        elementos = 0;

        for (int i = 0; i < tam; i++)
            ocupado[i] = false;
    }

    ~TablaHash(){
        delete[] tabla;
        delete[] ocupado;
    }

    int funcionHash(int clave){
        return clave % tam;
    }

    int funcionHashNegativa(int clave){
        int r = clave % tam;
        if (r < 0)
            r = r + tam;
        return r;
    }

    int funcionHash2(int clave){
        double A = 0.6180339887;
        double fraccion = (clave * A) - int(clave * A);
        int hash = int(tam * fraccion);
        return hash;
    }

    float factorCarga(){
        return (float) elementos/tam;
    }

    void insertar(Paciente p){
        int pos = funcionHash2(p.idPaciente);
        int intentos = 0;

        while(ocupado[pos] && intentos < tam){
            pos = (pos + 1) % tam;
            intentos++;
            colisiones++;
        }   
        if (intentos < tam){
            tabla[pos] = p;
            ocupado[pos] = true;
            elementos++;
        } else {
            cout << "Tabla llena" << endl;
        }
    }

    void buscar(int clave){
        int pos = funcionHash2(clave);
        int intentos = 0;

        while (ocupado[pos] && intentos < tam){
            if (tabla[pos].idPaciente == clave){
                cout << "Paciente encontrado en " << pos << ":\n";
                cout << pos << " --> ID: " << tabla[pos].idPaciente << " | Nombre: " << tabla[pos].nombre << " | Urgencia: " << tabla[pos].nivelUrg << endl;
                return;
            }
            pos = (pos + 1) % tam;
            intentos++;
        }
        cout << "Paciente no encontrado" << endl; 
        
    }
    void imprimir(){
        for(int i = 0; i < tam; i++)
            if (ocupado[i]){
                cout << i << " --> ID: " << tabla[i].idPaciente << " | Nombre: " << tabla[i].nombre << " | Urgencia: " << tabla[i].nivelUrg << endl;
            } else {
                cout << i << " --> " << endl;
            }
    }

    int numeroColisiones(){
        return colisiones;
    }

};

