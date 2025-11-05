#pragma once

#include "hash.h"
#include "AVL.h"           
#include "maxheap.h"          
#include "Paciente.h"

class SistemaTriage {
private:
    Hash tablaHash;
    AVL arbolCitas;
    MaxHeap maxHeap;
    const char* generarFechaCita();
    
public:
    SistemaTriage(int tamTabla = 10000);
    void registrarPaciente(int id, const char* nombre, int nivelUrgencia);
    void atenderSiguiente();
    void buscarPaciente(int id);
    void mostrarEstado();
    void mostrarCitas();

};