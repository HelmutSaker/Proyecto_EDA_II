#include <iostream>
using namespace std;
struct Paciente{
    int idPaciente;
    string nombre;
    int nivelUrg;
};

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
    void insert(Paciente key){
        int index = hashFunction(key.idPaciente);
        int tmp = index;
        while(ocupado[index]){
           index = (index+1)%SIZE;
            if(index==tmp){
                cout<<"la tabla esta llena"<<endl;
                return;
            }
        }
        tabla[index] = key;
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

int main()
{
    Hash tablitahash;

    Paciente p1 = {1, "Andrea", 3};
    tablitahash.insert(p1);
    tablitahash.print();
    return 0;
}
