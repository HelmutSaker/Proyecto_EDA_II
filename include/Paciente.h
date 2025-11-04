#ifndef PACIENTE_H
#define PACIENTE_H


class Paciente {
public:
    int idPaciente;
    char nombre[100];  
    int nivelUrgencia;
    char fechaCita[50];
    
    Paciente(int id = 0, const char* nom = "", int nivel = 0, const char* fecha = "") {
        idPaciente = id;
        nivelUrgencia = nivel;
        

        int i = 0;
        while(nom[i] != '\0' && i < 99) {
            nombre[i] = nom[i];
            i++;
        }
        nombre[i] = '\0';
        
        i = 0;
        while(fecha[i] != '\0' && i < 49) {
            fechaCita[i] = fecha[i];
            i++;
        }
        fechaCita[i] = '\0';
    }
};

#endif