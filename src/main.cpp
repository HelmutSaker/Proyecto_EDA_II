#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "../include/Paciente.h"
#include "../include/hash.h"
#include "../include/maxheap.h"
#include "../include/avl.h"
using namespace std;

class SistemaTriage {
private:
    Hash tablaHash;
    MaxHeap* colaUrgencia;
    int capacidadHeap;

public:
    SistemaTriage(int capacidad = 10000) : capacidadHeap(capacidad) {
        colaUrgencia = new MaxHeap(capacidad);
    }

    ~SistemaTriage() {
        delete colaUrgencia;
    }

    // Funcionalidad 1: Registro de pacientes
    void registrarPaciente(int id, string nombre, int urgencia) {
        if (urgencia < 1 || urgencia > 5) {
            cout << "Error: Nivel de urgencia debe ser entre 1-5" << endl;
            return;
        }

        Paciente nuevoPaciente(id, nombre, urgencia);
        
        // Insertar en tabla hash
        tablaHash.insert(nuevoPaciente);
        
        // Insertar en max-heap
        colaUrgencia->insert(nuevoPaciente);
        
        cout << "Paciente registrado exitosamente!" << endl;
    }

    // Cargar pacientes desde archivo
    void cargarDesdeArchivo(string nombreArchivo, ArbolAVL& arbolCitas) {
        ifstream archivo(nombreArchivo);
        if (!archivo.is_open()) {
            cout << "Error: No se pudo abrir el archivo " << nombreArchivo << endl;
            return;
        }

        string linea;
        int contador = 0;
        
        while (getline(archivo, linea)) {
            stringstream ss(linea);
            string idStr, nombre, urgenciaStr;
            string fecha, hora;
            
            if (getline(ss, idStr, ',') && getline(ss, nombre, ',') && getline(ss, urgenciaStr,',')&& getline(ss, fecha, ',') && getline(ss, hora)) {
                try {
                    int id = stoi(idStr);
                    int urgencia = stoi(urgenciaStr);
                    
                    if (urgencia >= 1 && urgencia <= 5) {
                        registrarPaciente(id, nombre, urgencia);
                        contador++;
                        arbolCitas.insertarR(fecha, hora);
                    }
                } catch (const exception& e) {
                    cout << "Error en linea: " << linea << endl;
                }
            }
        }
        
        archivo.close();
        cout << "Se cargaron " << contador << " pacientes desde el archivo." << endl;
    }

    // Funcionalidad 2: Atención de pacientes
    void atenderSiguiente() {
        if (colaUrgencia->getSize() == 0) {
            cout << "No hay pacientes en espera para atender." << endl;
            return;
        }

        // Extraer el paciente más urgente del heap
        Paciente pacienteAtendido = colaUrgencia->extractMax();
        
        // Buscar en la hash table para obtener datos completos
        Paciente* pacienteHash = tablaHash.buscarPaciente(pacienteAtendido.idPaciente);
        
        if (pacienteHash != nullptr) {
            // Marcar como atendido
            pacienteHash->atendido = true;
            
            cout << "\n=== PACIENTE ATENDIDO ===" << endl;
            cout << "ID: " << pacienteHash->idPaciente << endl;
            cout << "Nombre: " << pacienteHash->nombre << endl;
            cout << "Nivel de urgencia: " << pacienteHash->nivelUrgencia << endl;
            cout << "=========================" << endl;
        } else {
            cout << "Error: Paciente no encontrado en el sistema." << endl;
        }
    }

    // Mostrar estado del sistema
    void mostrarEstado() {
        cout << "\n=== ESTADO DEL SISTEMA ===" << endl;
        cout << "Pacientes en espera: " << colaUrgencia->getSize() << endl;
        cout << "Pacientes registrados: " << tablaHash.numElementos << endl;
        
        if (colaUrgencia->getSize() > 0) {
            cout << "\nPróximos pacientes en espera (ordenados por urgencia):" << endl;
            colaUrgencia->print();
        }
    }

    // Consultar paciente
    void consultarPaciente(int id) {
        tablaHash.mostrarPaciente(id);
    }
};

int main() {
    SistemaTriage sistema;
    int accion = 0;
    ArbolAVL arbolCitas;
    while (true) {
        cout << "\n=== SISTEMA DE TRIAGE HOSPITALARIO ===" << endl;
        cout << "Seleccione la accion a realizar (1-6): " << endl;
        cout << "1. Registrar pacientes" << endl;
        cout << "2. Atender pacientes" << endl;
        cout << "3. Asignar cita" << endl;
        cout << "4. Cancelar cita" << endl;
        cout << "5. Reprogramar cita" << endl;
        cout << "6. Consultar paciente" << endl;
        cout << "7. Mostrar estado del sistema" << endl;
        cout << "8. Salir" << endl;
        cout << "Opcion: ";
        
        cin >> accion;

        if (accion == 1) {
            int decision;
            cout << "\n=== REGISTRO DE PACIENTES ===" << endl;
            cout << "1. Cargar desde archivo .txt" << endl;
            cout << "2. Registro manual" << endl;
            cout << "Opcion: ";
            cin >> decision;

            if (decision == 1) {
                string nombreArchivo;
                cout << "Ingrese el nombre del archivo: ";
                cin >> nombreArchivo;
                sistema.cargarDesdeArchivo(nombreArchivo,arbolCitas);
            } else if (decision == 2) {
                int id, nUrg;
                string nombre;
                cout << "Ingrese ID: ";
                cin >> id;
                cout << "Ingrese nombre: ";
                cin.ignore();
                getline(cin, nombre);
                cout << "Nivel de urgencia (1-5): ";
                cin >> nUrg;
                sistema.registrarPaciente(id, nombre, nUrg);
            }
        }
        else if (accion == 2) {
            cout << "\n=== ATENCION DE PACIENTES ===" << endl;
            sistema.atenderSiguiente();
        }
        else if (accion == 3) {
            cout << "\n=== ASIGNAR CITA ===" << endl;
            string n, h;
            cout << "Ingrese fecha (DD/MM/AAAA): ";
            cin >> n;
            cout << "Ingrese hora (HH:MM): ";
            cin >> h;
            arbolCitas.insertarR(n,h);
        }
        else if (accion == 4) {
            cout << "\n=== CANCELAR CITA ===" << endl;
            string n, h;
            cout << "Ingrese fecha (DD/MM/AAAA): ";
            cin >> n;
            cout << "Ingrese hora (HH:MM): ";
            cin >> h;
            arbolCitas.eliminarR(n,h);
        }
        else if (accion == 5) {
            cout << "\n=== REPROGRAMAR CITA ===" << endl;
            string fechaV, horaV, fechaN, horaN;
            cout << "Ingrese fecha actual (DD/MM/AAAA): ";
            cin >> fechaV;
            cout << "Ingrese hora actual (HH:MM): ";
            cin >> horaV;
            cout << "Ingrese nueva fecha (DD/MM/AAAA): ";
            cin >> fechaN;
            cout << "Ingrese nueva hora (HH:MM): ";
            cin >> horaN;
            arbolCitas.editarR(fechaV, horaV, fechaN, horaN);
        }
        else if (accion == 6) {
            int id;
            cout << "\n=== CONSULTA DE PACIENTE ===" << endl;
            cout << "Ingrese ID del paciente: ";
            cin >> id;
            sistema.consultarPaciente(id);
        }
        else if (accion == 7) {
            sistema.mostrarEstado();
        }
        else if (accion == 8) {
            cout << "Saliendo del sistema..." << endl;
            break;
        }
        else {
            cout << "Funcionalidad " << accion << " aún no implementada." << endl;
        }
    }

    return 0;
}