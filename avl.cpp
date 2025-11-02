#include <iostream>
using namespace std;
class Node{
    private:
        int dato;
        int altura;
        Node * izquierda;
        Node * derecha;
    public:
        Node(int n){
            dato = n;
            altura = 1;
            izquierda = nullptr;
            derecha = nullptr;
        }
        int getDato() { return dato; }
        int getAltura() { return altura; }
        Node* getIzquierda() { return izquierda; }
        Node* getDerecha() { return derecha; }
    
        void setDato(int valor) { dato = valor; }
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
        
        void insertarR(int n){
            insertar(raiz, n);
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
        
        void insertar(Node*& nodo, int n){
            if(nodo==nullptr){
                nodo = new Node(n);
            }
            else if (n< nodo->getDato()){
                Node * tmp = nodo->getIzquierda();
                insertar(tmp, n);
                nodo->setIzquierda (tmp);
            }
            else{
                Node * tmp = nodo->getDerecha();
                insertar(tmp, n);
                nodo->setDerecha (tmp);
            }
            
            actualizarAltura(nodo);
            int facBalance = factorBalance(nodo);
            
            // der - der
            if (facBalance < -1 && n > nodo->getDerecha()->getDato()) {
                nodo = rotacionIzquierda(nodo);
            }
            // izq - izq
            if (facBalance > 1 && n < nodo->getIzquierda()->getDato()) {
                nodo = rotacionDerecha(nodo);
            }
            // izq - der
            if (facBalance > 1 && n > nodo->getIzquierda()->getDato() ) {
                Node *tmp = rotacionIzquierda(nodo->getIzquierda());
                nodo->setIzquierda(tmp);
                nodo = rotacionDerecha(nodo);
            }
            // der - izq
            if (facBalance < -1 && n < nodo->getDerecha()->getDato()) {
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
                cout << nodo->getDato() << " ";
                inorder(nodo->getDerecha());
            }
        }
        
        void preorder(Node *nodo) {
            if(nodo != nullptr) {
                cout << nodo->getDato() << " ";
                preorder(nodo->getIzquierda());
                preorder(nodo->getDerecha());
            }
        }
        
        bool buscarR(int n){
            return buscar(raiz, n);
        }
        bool buscar(Node* nodo, int n){
            if (nodo == nullptr) 
                return false;
            if (n == nodo->getDato()) 
                return true;
            if (n < nodo->getDato())
                return buscar(nodo->getIzquierda(), n);
            else
                return buscar(nodo->getDerecha(), n);
        }
        

};
int main() {
    ArbolAVL arbolito;
    arbolito.insertarR(50);
    arbolito.preorderR(); cout << endl;
    arbolito.insertarR(30);
    arbolito.preorderR(); cout << endl;
    arbolito.insertarR(70);
    arbolito.preorderR(); cout << endl;
    arbolito.insertarR(21);
    arbolito.preorderR(); cout << endl;
    arbolito.insertarR(47);
    arbolito.preorderR(); cout << endl;
    arbolito.insertarR(90);
    arbolito.preorderR(); cout << endl;
    arbolito.insertarR(100);
    arbolito.preorderR(); cout << endl;
    arbolito.insertarR(60);
    arbolito.insertarR(55);
    arbolito.preorderR(); cout << endl;
    return 0;
}