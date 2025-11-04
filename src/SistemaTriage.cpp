#include "SistemaTriage.h"
#include <iostream>
using namespace std;

void copiarString(char* destino, const char* origen) {
    int i = 0;
    while (origen[i] != '\0' && i < 49) {
        destino[i] = origen[i];
        i++;
    }
    destino[i] = '\0';
}

SistemaTriage::SistemaTriage(int tamTabla) : tablaHash() {
}

const char* SistemaTriage::generarFechaCita() {
    return "Cita por asignar";
}

void SistemaTriage::registrarPaciente(int id, const char* nombre, int nivelUrgencia) {
    if(nivelUrgencia < 1 || nivelUrgencia > 5) {
        cout << "Error: El nivel de urgencia debe estar entre 1 y 5" << endl;
        return;
    }
    
    int pos = tablaHash.hashFunction(id);
    int temp = pos;
    bool existe = false;
    
    while (tablaHash.ocupado[pos]) {
        if (tablaHash.tabla[pos].idPaciente == id) {
            existe = true;
            break;
        }
        pos = (pos + 1) % tablaHash.SIZE;
        if (pos == temp) break;
    }
    
    if(existe) {
        cout << "Error: Ya existe un paciente con ID " << id << endl;
        return;
    }
    
    Paciente* nuevoPaciente = new Paciente(id, nombre, nivelUrgencia);
    
    tablaHash.insert(*nuevoPaciente);
    minHeap.insertar(nuevoPaciente); 
    
    cout << "Paciente registrado exitosamente:" << endl;
    cout << "ID: " << id << ", Nombre: " << nombre 
         << ", Nivel de urgencia: " << nivelUrgencia << endl;
}

void SistemaTriage::atenderSiguiente() {
    Paciente* siguiente = minHeap.extraerMin();
    
    if(siguiente != nullptr) {
        copiarString(siguiente->fechaCita, generarFechaCita());
        
        arbolCitas.insertarPaciente(siguiente->idPaciente, siguiente);
        cout << "Cita programada para: " << siguiente->nombre 
             << " (ID: " << siguiente->idPaciente << ")" << endl;
        
        cout << "=== PACIENTE ATENDIDO ===" << endl;
        cout << "ID: " << siguiente->idPaciente << endl;
        cout << "Nombre: " << siguiente->nombre << endl;
        cout << "Nivel de urgencia: " << siguiente->nivelUrgencia << endl;
        cout << "Cita de seguimiento: " << siguiente->fechaCita << endl;
        cout << "========================" << endl;
        
        int pos = tablaHash.hashFunction(siguiente->idPaciente);
        int temp = pos;
        
        while (tablaHash.ocupado[pos]) {
            if (tablaHash.tabla[pos].idPaciente == siguiente->idPaciente) {
                tablaHash.ocupado[pos] = false;
                tablaHash.numElementos--;
                break;
            }
            pos = (pos + 1) % tablaHash.SIZE;
            if (pos == temp) break;
        }
    } else {
        cout << "No hay pacientes en espera" << endl;
    }
}

void SistemaTriage::buscarPaciente(int id) {
    int pos = tablaHash.hashFunction(id);
    int temp = pos;
    Paciente* pacienteEncontrado = nullptr;
    
    while (tablaHash.ocupado[pos]) {
        if (tablaHash.tabla[pos].idPaciente == id) {
            pacienteEncontrado = &tablaHash.tabla[pos];
            break;
        }
        pos = (pos + 1) % tablaHash.SIZE;
        if (pos == temp) break;
    }
    
    if(pacienteEncontrado != nullptr) {
        cout << "Paciente encontrado (en espera):" << endl;
        cout << "ID: " << pacienteEncontrado->idPaciente 
             << ", Nombre: " << pacienteEncontrado->nombre 
             << ", Urgencia: " << pacienteEncontrado->nivelUrgencia << endl;
    } else {
        Paciente* pacienteAtendido = arbolCitas.buscarPaciente(id);
        if(pacienteAtendido != nullptr) {
            cout << "Paciente encontrado (ya atendido):" << endl;
            cout << "ID: " << pacienteAtendido->idPaciente 
                 << ", Nombre: " << pacienteAtendido->nombre 
                 << ", Cita: " << pacienteAtendido->fechaCita << endl;
        } else {
            cout << "Paciente con ID " << id << " no encontrado" << endl;
        }
    }
}

void SistemaTriage::mostrarEstado() {
    cout << "\n=== ESTADO DEL SISTEMA DE TRIAGE ===" << endl;
    cout << "Pacientes en espera: " << tablaHash.numElementos << endl;
    cout << "Factor de carga tabla hash: " << (float)tablaHash.numElementos / tablaHash.SIZE << endl;
    cout << "Pacientes en cola de urgencia: " << minHeap.getSize() << endl;

    if(minHeap.getSize() > 0) {
        minHeap.imprimir();
    }
}

void SistemaTriage::mostrarCitas() {
    arbolCitas.mostrarPacientes();
}