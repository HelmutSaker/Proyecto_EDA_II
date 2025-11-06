#pragma once
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;
class Node{
    private:
        vector<int> fecha;
        vector<int> horaI;
        string horaS;
        string fechaS;
        int altura;
        Node * izquierda;
        Node * derecha;
    public:
        Node(string n,string h){
            altura = 1;
            izquierda = nullptr;
            derecha = nullptr;
            setFecha(n);
            setHoraS(h);
            horaS = h;
            fechaS = n;   
        }
        vector<int> getFecha() { return fecha; }
        vector<int> getHoraS() { return horaI; }
        string getHoraString() { return horaS; }
        string getFechaString() { return fechaS; }
        int getAltura() { return altura; }
        Node* getIzquierda() { return izquierda; }
        Node* getDerecha() { return derecha; }
    
        void setFecha(string valor) {
            vector<int> fechaInt;
            stringstream ss(valor);
            string segment;
            while (getline(ss, segment, '/')) {
                fechaInt.push_back(stoi(segment));
            }
            if(fechaInt[1]>12||fechaInt[1]<0){
                cout<<"Mes invalido"<<endl;
                return;
            }
            if(fechaInt[0]>31||fechaInt[0]<0){
                cout<<"Dia invalido"<<endl;
                return;
            }
            fecha = fechaInt;
        }
        void setHoraS(string valor) { 
            vector<int> horaInt;
            stringstream ss(valor);
            string segment;
            while (getline(ss, segment, ':')) {
                horaInt.push_back(stoi(segment));
            }
            if(horaInt[0]>23||horaInt[0]<0){
                cout<<"Hora invalida"<<endl;
                return;
            }
            if(horaInt[1]>59||horaInt[1]<0){
                cout<<"Minuto invalido"<<endl;
                return;
            }
            horaI = horaInt;
        }
        void setAltura(int valor) { altura = valor; }
        void setIzquierda(Node* nodo) { izquierda = nodo; }
        void setDerecha(Node* nodo) { derecha = nodo; }
};

class ArbolAVL{
    private:
        Node* raiz;
    public:
        ArbolAVL(){
            raiz = nullptr;
        }
        
        int altura(Node *nodo) {
            return nodo ? nodo->getAltura() : 0;
        }
        
        int factorBalance(Node *nodo) {
            /*if (nodo != nullptr)
                return altura(nodo->getIzquierda()) - altura(nodo->getDerecha());
            else
                return 0;*/
            return nodo ? altura(nodo->getIzquierda()) - altura(nodo->getDerecha()) : 0;
        }
        
        void actualizarAltura(Node *nodo) {
            int alt = 1 + max(altura(nodo->getIzquierda()), altura(nodo->getDerecha()));
            nodo->setAltura(alt);
        }
        
        void insertarR(string n,string h) {
            insertar(raiz, n,h);
        }
        
        Node * rotacionIzquierda(Node *actualRaiz) {
            Node *nuevaRaiz = actualRaiz->getDerecha();;
            Node *subArbol = nuevaRaiz->getIzquierda();
            
            nuevaRaiz->setIzquierda(actualRaiz);
            actualRaiz->setDerecha(subArbol);
            
            actualizarAltura(actualRaiz);
            actualizarAltura(nuevaRaiz);
            
            return nuevaRaiz;
        }
        
        Node * rotacionDerecha(Node *actualRaiz) {
            Node *nuevaRaiz = actualRaiz->getIzquierda();;
            Node *subArbol = nuevaRaiz->getDerecha();
            
            nuevaRaiz->setDerecha(actualRaiz);
            actualRaiz->setIzquierda(subArbol);
            
            actualizarAltura(actualRaiz);
            actualizarAltura(nuevaRaiz);
            
            return nuevaRaiz;
        }
        vector<int> Fecha(string valor) {
        vector<int> fechaInt; stringstream ss(valor); string segment; 
            while (getline(ss, segment, '/')) { 
            if(segment.empty()) return {};
            fechaInt.push_back(stoi(segment)); }
            if(fechaInt.size() != 3) return {}; 
            if(fechaInt[1]>12||fechaInt[1]<0){ 
                cout<<"Mes invalido"<<endl; 
                return {}; 
            } 
            if(fechaInt[0]>31||fechaInt[0]<0){ 
                cout<<"Dia invalido"<<endl; 
                return {}; 
            } return fechaInt; }
        vector<int> HoraS(string valor) { 
            vector<int> horaInt;
            stringstream ss(valor);
            string segment;
            while (getline(ss, segment, ':')) {
                if(segment.empty()) return {};
                horaInt.push_back(stoi(segment));
            }
            if(horaInt.size() != 2) return {};
            if(horaInt[0]>23||horaInt[0]<0){
                cout<<"Hora invalida"<<endl;
                return {};
            }
            if(horaInt[1]>59||horaInt[1]<0){
                cout<<"Minuto invalido"<<endl;
                return {};
            }
            return horaInt;
        }
        bool FechaIzquierda(vector<int> f1, vector<int> f2){
            if(f1[2]< f2[2] ||
               (f1[2]== f2[2] && f1[1]< f2[1]) ||
               (f1[2]== f2[2] && f1[1]== f2[1] && f1[0]< f2[0]) ){
                return true;
            }
            return false;
        }
        bool FechaDerecha(vector<int> f1, vector<int> f2){
            if(f1[2]> f2[2] ||
               (f1[2]== f2[2] && f1[1]> f2[1]) ||
               (f1[2]== f2[2] && f1[1]== f2[1] && f1[0]> f2[0]) ){
                return true;
            }
            return false;
        }
        bool FechaIgual(vector<int> f1, vector<int> f2){
            if(f1[2]== f2[2] && f1[1]== f2[1] && f1[0]== f2[0]){
                return true;
            }
            return false;
        }
        bool HoraIzquierda(vector<int> f1, vector<int> f2){
            if(f1[1]< f2[1] ||
               (f1[1]== f2[1] && f1[0]< f2[0])){
                return true;
            }
            return false;
        }
        bool HoraDerecha(vector<int> f1, vector<int> f2){
            if(f1[1]> f2[1] ||
               (f1[1]== f2[1] && f1[0]> f2[0]) ){
                return true;
            }
            return false;
        }
        bool HoraIgual(vector<int> f1, vector<int> f2){
            if(f1[1]== f2[1] && f1[0]== f2[0]){
                return true;
            }
            return false;
        }
        void insertar(Node*& nodo, string n, string h) {
            
            if(nodo==nullptr){
                nodo = new Node(n,h);
            }
            else if (FechaIzquierda(Fecha(n), nodo->getFecha())) {
                Node * tmp = nodo->getIzquierda();
                insertar(tmp, n,h);
                nodo->setIzquierda (tmp);
            }
            else if(FechaIgual(Fecha(n), nodo->getFecha())){
                if(HoraIgual(HoraS(h), nodo->getHoraS())){
                    cout<<"Fecha y hora ya ocupada"<<endl;
                    return;
                }else if(HoraIzquierda(HoraS(h), nodo->getHoraS())){
                    Node * tmp = nodo->getIzquierda();
                    insertar(tmp, n,h);
                    nodo->setIzquierda (tmp);
                }else{
                    Node * tmp = nodo->getDerecha();
                    insertar(tmp, n,h);
                    nodo->setDerecha (tmp);
                }
            }
            else{
                Node * tmp = nodo->getDerecha();
                insertar(tmp, n,h);
                nodo->setDerecha (tmp);
            }
            
            actualizarAltura(nodo);
            int facBalance = factorBalance(nodo);
            
            // der - der
            if (facBalance < -1 && nodo->getDerecha() && FechaDerecha(Fecha(n), nodo->getDerecha()->getFecha())) {
                nodo = rotacionIzquierda(nodo);
            }
            // izq - izq
            if (facBalance > 1 && nodo->getIzquierda()&& FechaIzquierda(Fecha(n), nodo->getIzquierda()->getFecha())) {
                nodo = rotacionDerecha(nodo);
            }
            // izq - der
            if (facBalance > 1 && nodo->getDerecha()&& FechaDerecha(Fecha(n), nodo->getIzquierda()->getFecha()) ) {
                Node *tmp = rotacionIzquierda(nodo->getIzquierda());
                nodo->setIzquierda(tmp);
                nodo = rotacionDerecha(nodo);
            }
            // der - izq
            if (facBalance < -1 && nodo->getIzquierda()&& FechaIzquierda(Fecha(n), nodo->getDerecha()->getFecha()) ) {
                Node *tmp = rotacionDerecha(nodo->getDerecha());
                nodo->setDerecha(tmp);
                nodo = rotacionIzquierda(nodo);
            }
        }
        
        void inorderR(){
            inorder(raiz);
        }
        
        void preorderR() {
            preorder(raiz);
        }
        
        void inorder(Node*nodo){
            if(nodo!=nullptr){
                inorder(nodo->getIzquierda());
                cout << nodo->getFechaString() <<" "<<nodo->getHoraString()<< " | ";
                inorder(nodo->getDerecha());
            }
        }
        
        void preorder(Node *nodo) {
            if(nodo != nullptr) {
                cout << nodo->getFechaString() <<" "<<nodo->getHoraString()<< " | ";
                preorder(nodo->getIzquierda());
                preorder(nodo->getDerecha());
            }
        }
        
        bool buscarR(string n,string h){
            return buscar(raiz, n,h);
        }
        bool buscar(Node* nodo, string n,string h)
        {
            if (nodo == nullptr) 
                return false;
            if (FechaIgual(Fecha(n), nodo->getFecha())&&HoraIgual(HoraS(h), nodo->getHoraS()))
                return true;
            if(FechaIgual(Fecha(n), nodo->getFecha())&&!HoraIgual(HoraS(h), nodo->getHoraS())){
                if(HoraIzquierda(HoraS(h), nodo->getHoraS()))
                    return buscar(nodo->getIzquierda(), n,h);
                else
                    return buscar(nodo->getDerecha(), n,h);
            }
            if (FechaIzquierda(Fecha(n), nodo->getFecha()))
                return buscar(nodo->getIzquierda(), n,h);
            else
                return buscar(nodo->getDerecha(), n,h);
        }
        Node* minValueNode(Node* nodo) {
            Node* tmp = nodo;
            while (tmp->getIzquierda() != nullptr) tmp = tmp->getIzquierda();
            return tmp;
        }
        Node* eliminar(Node* node, string n, string h) {
            if (node == nullptr) return node;
            vector<int> fechaN = Fecha(n);
            vector<int> horaN = HoraS(h);
            if(fechaN.empty() || horaN.empty()) return node;
            if (FechaIzquierda(fechaN, node->getFecha())){
                Node*tmp=node->getIzquierda();
                node->setIzquierda(eliminar(tmp, n, h));
            }
            else if (FechaDerecha(fechaN, node->getFecha())){
                Node*tmp=node->getDerecha();
                node->setDerecha(eliminar(tmp, n, h));
            }
            else {
                if(HoraIzquierda(horaN, node->getHoraS())){
                    Node*tmp=node->getIzquierda();
                    node->setIzquierda(eliminar(tmp, n, h));
                }
                else if(HoraDerecha(horaN, node->getHoraS())){
                    Node*tmp=node->getDerecha();
                    node->setDerecha(eliminar(tmp, n, h));
                }
                if (node->getIzquierda() == nullptr || node->getDerecha() == nullptr) {
                    Node* temp = node->getIzquierda() ? node->getIzquierda() : node->getDerecha();
                    if (temp == nullptr) {
                        delete node;
                        return nullptr;
                    } else {
                        Node* ret = temp;
                        delete temp;
                        return ret;
                    }
                } else {
                    Node* temp = minValueNode(node->getDerecha());
                    node->setFecha(n);
                    node->setHoraS(h);
                    node->setDerecha(eliminar(node->getDerecha(), n, h));
                }
            }

            actualizarAltura(node);

            int facBalance = factorBalance(node);

            if (facBalance > 1 && node->getIzquierda() && factorBalance(node->getIzquierda()) >= 0)
                return rotacionDerecha(node);
            if (facBalance > 1 && node->getIzquierda() && factorBalance(node->getIzquierda()) < 0) {
                node->setIzquierda(rotacionIzquierda(node->getIzquierda()));
                return rotacionDerecha(node);
            }
            if (facBalance < -1 && node->getDerecha() && factorBalance(node->getDerecha()) <= 0)
                return rotacionIzquierda(node);
            if (facBalance < -1 && node->getDerecha() && factorBalance(node->getDerecha()) > 0) {
                node->setDerecha(rotacionDerecha(node->getDerecha()));
                return rotacionIzquierda(node);
            }

            return node;
        }
        void eliminarR(string n, string h){
            if(!buscarR(n,h)){
                cout << "No se encontró la cita " << n << " " << h << endl;
            }else{
                cout << "Cita eliminada: " << n << " " << h << endl;
                eliminar(raiz, n, h);
            }
        }
        void editarR(string fechaV, string horaV, string fechaN, string horaN){
            if(!buscarR(fechaV, horaV)){
                cout << "Cita a editar no encontrada: " << fechaV << " " << horaV << endl;
            }else if(buscarR(fechaN, horaN)){
                cout << "Nueva fecha y hora ya ocupada: " << fechaN << " " << horaN << endl;
            }else{
                eliminar(raiz, fechaV, horaV);
                insertar(raiz, fechaN, horaN);
                cout << "Cita editada: " << fechaV << " " << horaV << " -> " << fechaN << " " << horaN << endl;
            }
        }
};