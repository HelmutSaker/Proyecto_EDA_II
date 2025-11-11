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
    Hash& getHashTable(){
        return tablaHash;
    }
    // Funcionalidad 1: Registro de pacientes
    void registrarPaciente(int id, string nombre, int urgencia,string fecha,string hora) {
        if (urgencia < 1 || urgencia > 5) {
            cout << "Error: Nivel de urgencia debe ser entre 1-5" << endl;
            return;
        }

        Paciente nuevoPaciente(id, nombre, urgencia,fecha,hora);
        
        // Insertar en tabla hash
        tablaHash.insert(nuevoPaciente);
        
        // Calcular indice hash
        int index = tablaHash.hashFunction(id);

        // Insertar en max-heap
        colaUrgencia->insert(nuevoPaciente.getUrgencia(), index);
        
        cout << "Paciente registrado exitosamente!" << endl;
    }

    // Cargar pacientes desde archivo
    void cargarDesdeArchivo(string nombreArchivo) {
        ifstream archivo(nombreArchivo);
        if (!archivo.is_open()) {
            cout << "Error: No se pudo abrir el archivo " << nombreArchivo << endl;
            return;
        }

        string linea;
        int contador = 0;
        
        while (getline(archivo, linea)) {
            stringstream ss(linea);
            string idStr, nombre, urgenciaStr,fecha,hora;           
            if (getline(ss, idStr, ',') && getline(ss, nombre, ',') && getline(ss, urgenciaStr,',')&& getline(ss, fecha, ',') && getline(ss, hora)) {
                try {
                    int id = stoi(idStr);
                    int urgencia = stoi(urgenciaStr);
                    if (urgencia >= 1 && urgencia <= 5) {
                        registrarPaciente(id, nombre, urgencia,fecha,hora);
                        contador++;
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
    void atenderSiguiente(ArbolAVL& arbolCitas) {
        if (colaUrgencia->getSize() == 0) {
            cout << "No hay pacientes en espera para atender." << endl;
            return;
        }

        // Extraer el paciente más urgente del heap
        tuple<int, int> maxUrg = colaUrgencia->extractMax();
        int urgencia = get<0>(maxUrg);
        int indexHash = get<1>(maxUrg);
        
        // Buscar en la hash table para obtener datos completos
        Paciente* pacienteHash = tablaHash.buscarPorIndex(indexHash);
        
        if (pacienteHash != nullptr) {
            pacienteHash->setAtendido(true);
            pacienteHash->setConCita(true);
            arbolCitas.insertarR(pacienteHash->getFecha(), pacienteHash->getHora(), tablaHash.hashFunction(pacienteHash->getId()));
            cout << "\n=== PACIENTE ATENDIDO ===" << endl;
            cout << "ID: " << pacienteHash->getId() << endl;
            cout << "Nombre: " << pacienteHash->getNombre() << endl;
            cout << "Nivel de urgencia: " << pacienteHash->getUrgencia() << endl;
            cout << "Fecha de cita: " << pacienteHash->getFecha() << endl;
            cout << "Hora de cita: " << pacienteHash->getHora() << endl;
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
    int getIndiceHash(int id){
        return tablaHash.hashFunction(id);
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
        cout << "3. Cancelar cita" << endl;
        cout << "4. Reprogramar cita" << endl;
        cout << "5. Consultar paciente" << endl;
        cout << "6. Mostrar estado del sistema" << endl;
        cout << "7. Mostrar estado de citas" << endl;
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
                sistema.cargarDesdeArchivo(nombreArchivo);
            } else if (decision == 2) {
                int id, nUrg;
                string nombre,fecha,hora;
                cout << "Ingrese ID: ";
                cin >> id;
                cout << "Ingrese nombre: ";
                cin.ignore();
                getline(cin, nombre);
                cout << "Nivel de urgencia (1-5): ";
                cin >> nUrg;
                cout << "Ingrese fecha cita(DD/MM/AAAA): ";
                cin >> fecha;
                cout << "Ingrese hora cita(HH:MM):";
                cin >> hora;
                sistema.registrarPaciente(id, nombre, nUrg,fecha,hora);
            }
        }
        else if (accion == 2) {
            cout << "\n=== ATENCION DE PACIENTES ===" << endl;
            sistema.atenderSiguiente(arbolCitas);
        }
        else if (accion == 3) {
            cout << "\n=== CANCELAR CITA ===" << endl;
            int n;
            cout << "Ingrese el id del paciente: ";
            cin >> n;
            Hash& hashRef = sistema.getHashTable();
            int idx = hashRef.hashFunction(n);
            Paciente* p = hashRef.buscarPorIndex(idx);
            if (p == nullptr) {
                cout << "Error: paciente con id " << n << " no encontrado en la tabla hash." << endl;
            } else {
                arbolCitas.eliminarR(idx);
                p->setConCita(false);
                p->setFecha("");
                p->setHora("");
                cout << "Cita cancelada para el paciente ID " << n << endl;
            }
        }
        else if (accion == 4) {
            cout << "\n=== REPROGRAMAR CITA ===" << endl;
            string fechaN, horaN;
            int n;
            cout << "Ingrese el id del paciente: ";
            cin >> n;
            cout << "Ingrese nueva fecha (DD/MM/AAAA): ";
            cin >> fechaN;
            cout << "Ingrese nueva hora (HH:MM): ";
            cin >> horaN;

            Hash& hashRef = sistema.getHashTable();
            int idx = hashRef.hashFunction(n);
            Paciente* p = hashRef.buscarPorIndex(idx);
            if (p == nullptr) {
                cout << "Error: paciente con id " << n << " no encontrado en la tabla hash." << endl;
            } else {
                arbolCitas.editarR(idx, fechaN, horaN);
                p->setFecha(fechaN);
                p->setHora(horaN);
                cout << "Cita reprogramada para ID " << n << " a " << fechaN << " " << horaN << endl;
            }
        }
        else if (accion == 5) {
            int id;
            cout << "\n=== CONSULTA DE PACIENTE ===" << endl;
            cout << "Ingrese ID del paciente: ";
            cin >> id;
            sistema.consultarPaciente(id);
        }
        else if (accion == 6) {
            sistema.mostrarEstado();
        }
        else if (accion == 7) {
            arbolCitas.inorderR();
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