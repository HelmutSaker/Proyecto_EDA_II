#pragma once
#include <string>
using namespace std;

class Paciente {
public:
    int idPaciente;
    string nombre;
    int nivelUrgencia;
    string fecha;
    string hora;
    
    Paciente(int id = 0, string nom = "", int nivel = 0, string n = "", string h = "") {
        idPaciente = id;
        nombre = nom;
        nivelUrgencia = nivel;
    }
};