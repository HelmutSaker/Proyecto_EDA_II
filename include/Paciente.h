#pragma once
#include <string>
using namespace std;

class Paciente {
private:
    int idPaciente;
    string nombre;
    int nivelUrgencia;
    string fecha;
    string hora;
    bool atendido;
    bool conCita;

public:    
    Paciente(int id = 0, string nom = "", int nivel = 0, string f = "", string h = "") {
        idPaciente = id;
        nombre = nom;
        nivelUrgencia = nivel;
        fecha = f;
        hora = h;
        atendido = false;
        conCita = false;
    }
};