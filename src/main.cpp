#include <iostream>
using namespace std;

int main() {

    int accion = 0;

    while (accion!=1 && accion!=2 && accion!=3 && accion!=4 && accion!=5 && accion!=6){
    
        cout << "BIENVENIDO" << endl << endl ;

        cout << "Seleccione la accion a realizar (1-6): " << endl << endl;

        cout << "1. Registrar pacientes" << endl;
        cout << "2. Atender pacientes" << endl;
        cout << "3. Asignar cita" << endl;
        cout << "4. Cancelar cita" << endl;
        cout << "5. Reprogramar cita" << endl;
        cout << "6. Consultar paciente" << endl << endl;

        cin >> accion;

    }

    if(accion==1)
    {
        int desicion;
        cout << "Desea importar .txt?" << endl;
        cout << "1. Si" << endl;
        cout << "2. No" << endl;
        cin >> desicion;

        if(desicion==2)
        {
            int id, nUrg;
            string nombre;
            cout << "Ingrese su id: ";
            cin >> id;
            cout << endl <<"Ingrese su nombre: ";
            cin >> nombre;
            cout << endl <<"Nivel de urgencia (1-5): ";
            cin >> nUrg;
        }
    }

    else if(accion==2)
    {

    }

    else if(accion==3)
    {
        
    }

    else if(accion==4)
    {
        
    }

    else if(accion==5)
    {
        
    }

    else if(accion==6)
    {
        
    }

    /*
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
    */

    return 0;
}