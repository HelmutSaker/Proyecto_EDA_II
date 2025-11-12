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
        int index;
    public:
        Node(string f,string h){
            altura = 1;
            izquierda = nullptr;
            derecha = nullptr;
            fecha.clear();
            horaI.clear();
            setFecha(f);
            setHoraS(h);
            horaS = h;
            fechaS = f;   
        }
        vector<int> getFecha() { return fecha; }
        vector<int> getHoraS() { return horaI; }
        string getHoraString() { return horaS; }
        string getFechaString() { return fechaS; }
        int getAltura() { return altura; }
        Node* getIzquierda() { return izquierda; }
        Node* getDerecha() { return derecha; }
        void setIndex(int valor) { index = valor; }
        int getIndex() { return index; }
        void setFecha(string valor) {
            vector<int> fechaInt;
            stringstream ss(valor);
            string segment;
            while (getline(ss, segment, '/')) {
                if(segment.empty()) return;
                fechaInt.push_back(stoi(segment));
            }
            if(fechaInt.size() != 3) return;
            if(fechaInt[1]>12||fechaInt[1]<0){
                cout<<"Mes invalido"<<endl;
                return;
            }
            if(fechaInt[0]>31||fechaInt[0]<0){
                cout<<"Dia invalido"<<endl;
                return;
            }
            fecha = fechaInt;
            fechaS = valor;
        }
        void setHoraS(string valor) { 
            vector<int> horaInt;
            stringstream ss(valor);
            string segment;
            while (getline(ss, segment, ':')) {
                if(segment.empty()) return;
                horaInt.push_back(stoi(segment));
            }
            if(horaInt.size() != 2) return;
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
            return nodo ? altura(nodo->getIzquierda()) - altura(nodo->getDerecha()) : 0;
        }
        
        void actualizarAltura(Node *nodo) {
            if(!nodo) return;
            int alt = 1 + max(altura(nodo->getIzquierda()), altura(nodo->getDerecha()));
            nodo->setAltura(alt);
        }
        
        void insertarR(string f,string h,int n) {
            insertar(raiz, f,h,n);
        }
        
        Node * rotacionIzquierda(Node *actualRaiz) {
            if(!actualRaiz) return nullptr;
            Node *nuevaRaiz = actualRaiz->getDerecha();
            if(!nuevaRaiz) return actualRaiz;
            Node *subArbol = nuevaRaiz->getIzquierda();
            
            nuevaRaiz->setIzquierda(actualRaiz);
            actualRaiz->setDerecha(subArbol);
            
            actualizarAltura(actualRaiz);
            actualizarAltura(nuevaRaiz);
            
            return nuevaRaiz;
        }
        
        Node * rotacionDerecha(Node *actualRaiz) {
            if(!actualRaiz) return nullptr;
            Node *nuevaRaiz = actualRaiz->getIzquierda();
            if(!nuevaRaiz) return actualRaiz;
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
                fechaInt.push_back(stoi(segment)); 
            }
            if(fechaInt.size() != 3) return {}; 
            if(fechaInt[1]>12||fechaInt[1]<0){ 
                cout<<"Mes invalido"<<endl; 
                return {}; 
            } 
            if(fechaInt[0]>31||fechaInt[0]<0){ 
                cout<<"Dia invalido"<<endl; 
                return {}; 
            } return fechaInt; 
        }
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
            if(f1.size()!=3 || f2.size()!=3) return false;
            if(f1[2]< f2[2] ||
               (f1[2]== f2[2] && f1[1]< f2[1]) ||
               (f1[2]== f2[2] && f1[1]== f2[1] && f1[0]< f2[0]) ){
                return true;
            }
            return false;
        }
        bool FechaDerecha(vector<int> f1, vector<int> f2){
            if(f1.size()!=3 || f2.size()!=3) return false;
            if(f1[2]> f2[2] ||
               (f1[2]== f2[2] && f1[1]> f2[1]) ||
               (f1[2]== f2[2] && f1[1]== f2[1] && f1[0]> f2[0]) ){
                return true;
            }
            return false;
        }
        bool FechaIgual(vector<int> f1, vector<int> f2){
            if(f1.size()!=3 || f2.size()!=3) return false;
            if(f1[2]== f2[2] && f1[1]== f2[1] && f1[0]== f2[0]){
                return true;
            }
            return false;
        }
        bool HoraIzquierda(vector<int> f1, vector<int> f2){
            if(f1.size()!=2 || f2.size()!=2) return false;
            if(f1[0]< f2[0] ||
               (f1[0]== f2[0] && f1[1]< f2[1])){
                return true;
            }
            return false;
        }
        bool HoraDerecha(vector<int> f1, vector<int> f2){
            if(f1.size()!=2 || f2.size()!=2) return false;
            if(f1[0]> f2[0] ||
               (f1[0]== f2[0] && f1[1]> f2[1]) ){
                return true;
            }
            return false;
        }
        bool HoraIgual(vector<int> f1, vector<int> f2){
            if(f1.size()!=2 || f2.size()!=2) return false;
            if(f1[1]== f2[1] && f1[0]== f2[0]){
                return true;
            }
            return false;
        }
        void insertar(Node*& nodo, string f, string h,int n) {
            vector<int> fechaN = Fecha(f);
            vector<int> horaN = HoraS(h);
            if (fechaN.empty() || horaN.empty()) return;
            if(nodo==nullptr){
                nodo = new Node(f,h);
                nodo->setIndex(n);
            }
            else if (FechaIzquierda(fechaN, nodo->getFecha())) {
                Node * tmp = nodo->getIzquierda();
                insertar(tmp, f,h,n);
                nodo->setIzquierda (tmp);
            }
            else if(FechaIgual(fechaN, nodo->getFecha())){
                if(HoraIgual(horaN, nodo->getHoraS())){
                    cout<<"Fecha y hora ya ocupada"<<endl;
                    return;
                }else if(HoraIzquierda(horaN, nodo->getHoraS())){
                    Node * tmp = nodo->getIzquierda();
                    insertar(tmp, f,h,n);
                    nodo->setIzquierda (tmp);
                }else{
                    Node * tmp = nodo->getDerecha();
                    insertar(tmp, f,h,n);
                    nodo->setDerecha (tmp);
                }
            }
            else{
                Node * tmp = nodo->getDerecha();
                insertar(tmp, f,h,n);
                nodo->setDerecha (tmp);
            }
            
            actualizarAltura(nodo);
            int facBalance = factorBalance(nodo);
            
            // der - der
            if (facBalance < -1 && nodo->getDerecha() && (FechaDerecha(fechaN, nodo->getDerecha()->getFecha())||(FechaIgual(fechaN, nodo->getDerecha()->getFecha())&&HoraDerecha(horaN, nodo->getDerecha()->getHoraS())))) {
                nodo = rotacionIzquierda(nodo);
            }
            // izq - izq
            if (facBalance > 1 && nodo->getIzquierda()&& (FechaIzquierda(fechaN, nodo->getIzquierda()->getFecha())||(FechaIgual(fechaN, nodo->getIzquierda()->getFecha())&&HoraIzquierda(horaN, nodo->getIzquierda()->getHoraS()))) ) {
                nodo = rotacionDerecha(nodo);
            }
            // izq - der
            if (facBalance > 1 && nodo->getIzquierda()&& (FechaDerecha(fechaN, nodo->getIzquierda()->getFecha())||(FechaIgual(fechaN, nodo->getIzquierda()->getFecha())&&HoraDerecha(horaN, nodo->getIzquierda()->getHoraS())) )) {
                Node *tmp = rotacionIzquierda(nodo->getIzquierda());
                nodo->setIzquierda(tmp);
                nodo = rotacionDerecha(nodo);
            }
            // der - izq
            if (facBalance < -1 && nodo->getDerecha()&& (FechaIzquierda(fechaN, nodo->getDerecha()->getFecha())||(FechaIgual(fechaN, nodo->getDerecha()->getFecha())&&HoraIzquierda(horaN, nodo->getDerecha()->getHoraS())) )) {
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
        Node* buscarNodoPorIndex(Node* nodo, int idx) {
            if (!nodo) return nullptr;
            if (nodo->getIndex() == idx) return nodo;
            Node* l = buscarNodoPorIndex(nodo->getIzquierda(), idx);
            if (l) return l;
            return buscarNodoPorIndex(nodo->getDerecha(), idx);
        }
        Node* minValueNode(Node* nodo) {
            if(!nodo) return nullptr;
            Node* tmp = nodo;
            while (tmp->getIzquierda() != nullptr) tmp = tmp->getIzquierda();
            return tmp;
        }
        Node* eliminarPorClave(Node* node, const vector<int>& fechaN, const vector<int>& horaN) {
            if (!node) return node;
            if (FechaIzquierda(fechaN, node->getFecha()) ||
                (FechaIgual(fechaN, node->getFecha()) && HoraIzquierda(horaN, node->getHoraS()))) {
                node->setIzquierda(eliminarPorClave(node->getIzquierda(), fechaN, horaN));
            }
            else if (FechaDerecha(fechaN, node->getFecha()) ||
                     (FechaIgual(fechaN, node->getFecha()) && HoraDerecha(horaN, node->getHoraS()))) {
                node->setDerecha(eliminarPorClave(node->getDerecha(), fechaN, horaN));
            }
            else {
                if (node->getIzquierda() == nullptr || node->getDerecha() == nullptr) {
                    Node* temp = node->getIzquierda() ? node->getIzquierda() : node->getDerecha();
                    if (temp == nullptr) {
                        delete node;
                        return nullptr;
                    } else {
                        Node* ret = temp;
                        delete node;
                        return ret;
                    }
                } else {
                    Node* temp = minValueNode(node->getDerecha());
                    node->setFecha(temp->getFechaString());
                    node->setHoraS(temp->getHoraString());
                    node->setIndex(temp->getIndex());
                    node->setDerecha(eliminarPorClave(node->getDerecha(), Fecha(temp->getFechaString()), HoraS(temp->getHoraString())));
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
        bool existeFechaHora(Node* nodo, const vector<int>& f, const vector<int>& h, int excludeIndex = -1) {
            if (!nodo) return false;
            if (FechaIgual(f, nodo->getFecha()) && HoraIgual(h, nodo->getHoraS()) && nodo->getIndex() != excludeIndex) return true;
            if (FechaIzquierda(f, nodo->getFecha()) || (FechaIgual(f, nodo->getFecha()) && HoraIzquierda(h, nodo->getHoraS())))
                return existeFechaHora(nodo->getIzquierda(), f, h, excludeIndex);
            else
                return existeFechaHora(nodo->getDerecha(), f, h, excludeIndex);
        }
        bool buscarR(int n){
            return buscarNodoPorIndex(raiz, n) != nullptr;
        }
        void eliminarR(int n){
            Node* objetivo = buscarNodoPorIndex(raiz, n);
            if (!objetivo) {
                cout << "No se encontró la cita" << endl;
                return;
            }
            vector<int> f = Fecha(objetivo->getFechaString());
            vector<int> h = HoraS(objetivo->getHoraString());
            if (f.empty() || h.empty()) {
                cout << "Error: datos de fecha/hora inválidos" << endl;
                return;
            }
            raiz = eliminarPorClave(raiz, f, h);
        }
        void editarR(int n, string fechaNstr, string horaNstr){
            Node* objetivo = buscarNodoPorIndex(raiz, n);
            if (!objetivo) {
                cout << "Cita a editar no encontrada" <<endl;
                return;
            }

            vector<int> nuevaF = Fecha(fechaNstr);
            vector<int> nuevaH = HoraS(horaNstr);
            if (nuevaF.empty() || nuevaH.empty()) {
                cout << "Fecha/hora nueva inválida" << endl;
                return;
            }
            if (existeFechaHora(raiz, nuevaF, nuevaH, n)) {
                cout << "Nueva fecha y hora ya ocupada: " << fechaNstr << " " << horaNstr << endl;
                return;
            }
            vector<int> oldF = Fecha(objetivo->getFechaString());
            vector<int> oldH = HoraS(objetivo->getHoraString());
            raiz = eliminarPorClave(raiz, oldF, oldH);
            insertar(raiz, fechaNstr, horaNstr, n);
        }
};