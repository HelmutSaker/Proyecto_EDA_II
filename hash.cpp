#include <iostream>
using namespace std;

class TablaHash{
    private:
        int* tabla;
        int tam;
        int colisiones;
        int elementos;
    public:
        TablaHash(int t){
            colisiones = 0;
            tam = t;
            tabla = new int[tam];
            elementos = 0;
            for (int i = 0; i < tam; i++)
                tabla[i]= -1;
        }
        int funcionHash(int clave){
            return clave%tam;
        }
        int funcionHashNegativa(int clave){
            int r = clave % tam;
            if (r < 0)
                r = r + tam;
            return r;
        }
        int funcionHash2(int clave){
            double A = 0.6180339887;
            double fraccion = (clave * A) - int(clave * A);
            int hash = int(tam * fraccion);
            return hash;
        }
        float factorCarga(){
            float carga = (float)elementos / tam;
            return carga;
        }

        void insertar(int clave){
            int pos = funcionHash2(clave);
            int intentos = 0;
            while (tabla[pos]!=-1&&intentos<tam)
            {
                pos = (pos +1) % tam;
                cout<< clave << "  "<<pos<<" ";
                intentos++;
                colisiones++;
            }
            cout<<endl;
            if(intentos<tam){
                tabla[pos] = clave;
                elementos++;
            }
            else
                cout<<"La tabla esta llena"<<endl;
        }
        int numeroColisiones(){
            return colisiones;
        }

        void imprimir(){
            for (int i = 0; i < tam; i++)
            {
                cout<<i<<": ";
                if(tabla[i]==-1)
                    cout<<" Vacio"<<endl;
                else
                    cout<<tabla[i]<<endl;
            }
            
        }


};

int main() {
    TablaHash tablitahash(10);
    tablitahash.insertar(-15);
    tablitahash.insertar(25);
    tablitahash.insertar(35);
    tablitahash.insertar(45);
    tablitahash.insertar(55);
    tablitahash.insertar(65);
    tablitahash.insertar(75);
    tablitahash.insertar(85);
    tablitahash.insertar(95);
    tablitahash.insertar(105);
    tablitahash.insertar(115);
    tablitahash.insertar(125);
    tablitahash.imprimir();


    return 0;
}