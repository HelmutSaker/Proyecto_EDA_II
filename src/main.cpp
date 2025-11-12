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
    SistemaTriage(int capacidad = 10007) : capacidadHeap(capacidad) {
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
    void atenderSiguiente() {
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
    void atenderNSiguiente(int N) {
        if (colaUrgencia->getSize() == 0) {
            cout << "No hay pacientes en espera para atender." << endl;
            return;
        }

        for(int i=0;i<N;i++){
        // Extraer el paciente más urgente del heap
        tuple<int, int> maxUrg = colaUrgencia->extractMax();
        int urgencia = get<0>(maxUrg);
        int indexHash = get<1>(maxUrg);
        
        // Buscar en la hash table para obtener datos completos
        Paciente* pacienteHash = tablaHash.buscarPorIndex(indexHash);
        if (pacienteHash != nullptr) {
            pacienteHash->setAtendido(true);
            cout << "\n=== PACIENTE ATENDIDO ===" << endl;
            cout << "ID: " << pacienteHash->getId() << endl;
            cout << "Nombre: " << pacienteHash->getNombre() << endl;
            cout << "Nivel de urgencia: " << pacienteHash->getUrgencia() << endl;
            cout << "Fecha de cita: " << pacienteHash->getFecha() << endl;
            cout << "Hora de cita: " << pacienteHash->getHora() << endl;
            cout << "=========================" << endl;
        } else {
            cout << "Error: Paciente no encontrado en el sistema." << endl;
        }}
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
        cout << "Seleccione la accion a realizar (1-9): " << endl;
        cout << "1. Registrar pacientes" << endl;
        cout << "2. Atender pacientes" << endl;
        cout << "3. Cancelar cita" << endl;
        cout << "4. Reprogramar cita" << endl;
        cout << "5. Consultar paciente" << endl;
        cout << "6. Mostrar estado del sistema" << endl;
        cout << "7. Mostrar estado de citas" << endl;
        cout << "8. Insertar cita" << endl;
        cout << "9. Salir" << endl;
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
            int decision;
            cout << "\n=== ATENCION DE PACIENTES ===" << endl;
            cout << "1. Atencion de un pacientes" << endl;
            cout << "2. Atencion de N pacientes" << endl;
            cout << "Opcion: ";
            cin >> decision;
            if (decision == 1) {
                cout << "\n=== ATENCION DE PACIENTES ===" << endl;
                sistema.atenderSiguiente();
            } else if (decision == 2) {
                cout << "\n=== ATENCION DE PACIENTES ===" << endl;
                int N;
                cout << "Ingrese la cantidad de pacientes a atender: ";
                cin >> N;
                sistema.atenderNSiguiente(N);
            } 
        }
        else if (accion == 3) {
            int decision;
            cout << "\n=== CANCELAR CITA ===" << endl;
            cout << "1. Cancelar una cita" << endl;
            cout << "2. Cancelar N citas" << endl;
            cout << "Opcion: ";
            cin >> decision;

            if (decision == 1) {
                int id;
                cout << "\n=== CANCELAR CITA ===" << endl;
                cout << "Ingrese ID del paciente: ";
                cin >> id;
                Hash& hashRef = sistema.getHashTable();
                int idx = hashRef.hashFunction(id);
                Paciente* p = hashRef.buscarPorIndex(idx);
                if (p == nullptr) {
                    cout << "Error: paciente con id " << id << " no encontrado en la tabla hash." << endl;
                } else {
                    if(!p->getConCita()){
                        cout << "Error: el paciente con id " << id << " no tiene una cita programada." << endl;
                    }else{
                        p->setConCita(false);
                        p->setFecha("");
                        p->setHora("");
                        arbolCitas.eliminarR(idx);
                        cout << "Cita cancelada para el paciente ID " << id << endl;
                    }
                }
            } else if (decision == 2) {
                int N;
                cout << "\n=== CANCELAR CITA ===" << endl;
                cout << "Ingrese la cantidad de citas a insertar: ";
                cin >> N;
                int id;
                cout << "Ingrese desde que id se desea citas a insertar: ";
                cin >> id;
                for(int i=0;i<N;i++){
                    Hash& hashRef = sistema.getHashTable();
                    int idx = hashRef.hashFunction(id);
                    Paciente* p = hashRef.buscarPorIndex(idx);
                    if (p == nullptr) {
                        cout << "Error: paciente con id " << id << " no encontrado en la tabla hash." << endl;
                    } else {
                        if(!p->getConCita()){
                            cout << "Error: el paciente con id " << id << " no tiene una cita programada." << endl;
                        }else{
                            p->setConCita(false);
                            p->setFecha("");
                            p->setHora("");
                            arbolCitas.eliminarR(idx);
                            cout << "Cita cancelada para el paciente ID " << id << endl;
                        }
                    }
                    id++;
                }
            }
        }
        else if (accion == 4) {

            int decision;
            cout << "\n=== REPROGRAMAR CITA ===" << endl;
            cout << "1. Reprogramar una cita" << endl;
            cout << "2. Reprogramar N citas" << endl;
            cout << "Opcion: ";
            cin >> decision;

            if (decision == 1) {
                int id;
                string fechaN, horaN;
                cout << "\n=== REPROGRAMAR CITA ===" << endl;
                cout << "Ingrese el id del paciente: ";
                cin >> id;
                cout << "Ingrese nueva fecha (DD/MM/AAAA): ";
                cin >> fechaN;
                cout << "Ingrese nueva hora (HH:MM): ";
                cin >> horaN;
                Hash& hashRef = sistema.getHashTable();
                int idx = hashRef.hashFunction(id);
                Paciente* p = hashRef.buscarPorIndex(idx);
                if (p == nullptr) {
                    cout << "Error: paciente con id " << id << " no encontrado en la tabla hash." << endl;
                } else {
                    if(!p->getConCita()){
                        cout << "Error: el paciente con id " << id << " no tiene una cita programada." << endl;
                    }else{
                        arbolCitas.editarR(idx, fechaN, horaN);
                        p->setFecha(fechaN);
                        p->setHora(horaN);
                        cout << "Cita reprogramada para ID " << id << " a " << fechaN << " " << horaN << endl;
                    }
                }
            } else if (decision == 2) {
                int N;
                cout << "\n=== REPROGRAMAR CITA ===" << endl;
                cout << "Ingrese la cantidad de citas a reprogramar: ";
                cin >> N;
                int id;
                cout << "Ingrese desde que id se desea las citas reprogramar: ";
                cin >> id;
                int id2;
                cout <<"Ingrese desde que id se optendran las nuevas fechas y horas: ";
                cin >> id2;
                for(int i=0;i<N;i++){
                    Hash& hashRef = sistema.getHashTable();
                    int idx = hashRef.hashFunction(id);
                    Paciente* p = hashRef.buscarPorIndex(idx);
                    Hash& hashRef2 = sistema.getHashTable();
                    int idx2 = hashRef2.hashFunction(id2);
                    Paciente* p2 = hashRef2.buscarPorIndex(idx2);
                    string fechaN = p2->getFecha();
                    string horaN = p2->getHora();
                    if (p == nullptr) {
                        cout << "Error: paciente con id " << id << " no encontrado en la tabla hash." << endl;
                    } else {
                        if(!p->getConCita()){
                            cout << "Error: el paciente con id " << id << " no tiene una cita programada." << endl;
                        }else{
                            if(arbolCitas.existeFechaHora(arbolCitas.getRaiz(),arbolCitas.Fecha(fechaN),arbolCitas.HoraS(horaN)))
                            {
                                cout<<"Cita ya existe en esta fecha no se puede insertar la cita"<<endl;
                            }else{
                                arbolCitas.editarR(idx, fechaN, horaN);
                                p->setFecha(fechaN);
                                p->setHora(horaN);
                                cout << "Cita reprogramada para ID " << id << " a " << fechaN << " " << horaN << endl;
                            }
                        }
                    }
                    id++;
                    id2++;
                }
            }
        }
        else if (accion == 5) {
            int decision;
            cout << "\n=== CONSULTAR PACIENTES ===" << endl;
            cout << "1. Consulta de un pacientes" << endl;
            cout << "2. Consulta de N pacientes" << endl;
            cout << "Opcion: ";
            cin >> decision;
            if (decision == 1) {
                int id;
                cout << "\n=== CONSULTAR PACIENTES ===" << endl;
                cout << "Ingrese ID del paciente: ";
                cin >> id;
                sistema.consultarPaciente(id);  
            } else if (decision == 2) {
                int N;
                int id;
                cout << "\n=== CONSULTAR PACIENTES ===" << endl;
                cout << "Ingrese la cantidad de pacientes a consultar: ";
                cin >> N;
                cout << "Ingrese desde que id se desea consultar: ";
                cin >> id;
                for(int i=0;i<N;i++){
                    sistema.consultarPaciente(id);  
                    id++;
                }
            }  
        }
        else if (accion == 6) {
            sistema.mostrarEstado();
        }
        else if (accion == 7) {
            arbolCitas.inorderR();
        }
        else if (accion == 8) {
            int decision;
            cout << "\n=== INSERTAR CITAS ===" << endl;
            cout << "1. Insertar cita:" << endl;
            cout << "2. Insertar N citas:" << endl;
            cout << "Opcion: ";
            cin >> decision;

            if (decision == 1) {
                string fecha,hora;
                int id;
                cout << "\n=== INSERTAR CITAS ===" << endl;
                cout << "Ingrese ID del paciente: ";
                cin >> id;
                cout << "Ingrese fecha cita(DD/MM/AAAA): ";
                cin >> fecha;
                cout << "Ingrese hora cita(HH:MM):";
                cin >> hora;
                Hash& hashRef = sistema.getHashTable();
                int idx = hashRef.hashFunction(id);
                Paciente* p = hashRef.buscarPorIndex(idx);
                if (p == nullptr) {
                    cout << "Error: paciente con id " << id << " no encontrado en la tabla hash." << endl;
                } else {
                    if(p->getConCita()){
                        cout << "Error: el paciente con id " << id << " ya tiene una cita programada." << endl;
                    }else{
                        p->setConCita(true);
                        p->setFecha(fecha);
                        p->setHora(hora);
                        if(arbolCitas.existeFechaHora(arbolCitas.getRaiz(),arbolCitas.Fecha(fecha),arbolCitas.HoraS(hora)))
                        {
                            cout<<"Cita ya existe en esta fecha no se puede insertar la cita"<<endl;
                        }else{
                            cout << "Cita insertada para el paciente ID " << id << endl;
                            arbolCitas.insertarR(fecha, hora, idx);
                        }
                    }
                }
            } else if (decision == 2) {
                string fecha,hora;
                int N;
                cout << "\n=== INSERTAR CITAS ===" << endl;
                cout << "Ingrese la cantidad de citas a insertar: ";
                cin >> N;
                int id;
                cout << "Ingrese desde que id se desea citas a insertar: ";
                cin >> id;
                for(int i=0;i<N;i++){
                    Hash& hashRef = sistema.getHashTable();
                    int idx = hashRef.hashFunction(id);
                    Paciente* p = hashRef.buscarPorIndex(idx);
                    if (p == nullptr) {
                        cout << "Error: paciente con id " << id << " no encontrado en la tabla hash." << endl;
                    } else {
                        if(p->getConCita()){
                            cout << "Error: el paciente con id " << id << " ya tiene una cita programada." << endl;
                        }else{
                            p->setConCita(true);
                            fecha=p->getFecha();
                            hora=p->getHora();
                            if(arbolCitas.existeFechaHora(arbolCitas.getRaiz(),arbolCitas.Fecha(fecha),arbolCitas.HoraS(hora)))
                            {
                                cout<<"Cita ya existe en esta fecha no se puede insertar la cita"<<endl;
                            }else{
                                cout << "Cita insertada para el paciente ID " << id << endl;
                                arbolCitas.insertarR(fecha, hora, idx);
                            }
                        }
                    }
                    id++;
                }
            }
        }
        else if (accion == 9) {
            cout << "Saliendo del sistema..." << endl;
            break;
        }
        else {
            cout << "Funcionalidad " << accion << " aún no implementada." << endl;
        }
    }

    return 0;
}