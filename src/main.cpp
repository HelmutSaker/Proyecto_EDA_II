#include "SistemaTriage.h"
#include <iostream>
using namespace std;

int main() {
    SistemaTriage sistema;
    

    cout << "=== DEMOSTRACION SISTEMA DE TRIAGE ===" << endl;

    cout << "\n=== REGISTRO DE PACIENTES ===" << endl;
    sistema.registrarPaciente(1001, "Juan Perez", 2);
    sistema.registrarPaciente(1002, "Maria Garcia", 1);
    sistema.registrarPaciente(1003, "Carlos Lopez", 4);
    sistema.registrarPaciente(1004, "Ana Martinez", 3);
    sistema.registrarPaciente(1005, "Pedro Rodriguez", 1);
    sistema.mostrarEstado();
    

    cout << "\n=== ATENCION DE PACIENTES ===" << endl;
    sistema.atenderSiguiente(); 
    sistema.atenderSiguiente(); 
    sistema.mostrarEstado();
    sistema.mostrarCitas();
    
    cout << "\n=== BUSQUEDAS ===" << endl;
    sistema.buscarPaciente(1002);
    sistema.buscarPaciente(1003); 
    sistema.buscarPaciente(9999); 
    
    return 0;
}