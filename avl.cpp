#include <iostream>
#include <algorithm>
using namespace std;

// -------------------- Clase Nodo --------------------
class Node {
public:
    int key;
    int height;
    Node* left;
    Node* right;

    Node(int k) {
        key = k;
        height = 0;     // una hoja comienza con altura 0
        left = NULL;
        right = NULL;
    }
};

// -------------------- Clase AVL --------------------
class AVL {
private:
    Node* root;

    int height(Node* n) {
        if (n == NULL) return -1;   // árbol vacío tiene altura -1
        return n->height;
    }

    int balance(Node* n) {
        if (n == NULL) return 0;
        return height(n->left) - height(n->right);
    }

    void updateHeight(Node* n) {
        if (n != NULL) {
            n->height = 1 + max(height(n->left), height(n->right));
        }
    }

    // Rotación derecha
    Node* rotateRight(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        updateHeight(y);
        updateHeight(x);

        return x;
    }

    // Rotación izquierda
    Node* rotateLeft(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        updateHeight(x);
        updateHeight(y);

        return y;
    }

    // -------------------- Insertar --------------------
    Node* insert(Node* node, int key) {
        if (node == NULL) return new Node(key);

        if (key < node->key)
            node->left = insert(node->left, key);
        else if (key > node->key)
            node->right = insert(node->right, key);
        else
            return node; // no se permiten duplicados

        updateHeight(node);

        int bf = balance(node);

        // Caso LL
        if (bf > 1 && key < node->left->key)
            return rotateRight(node);

        // Caso RR
        if (bf < -1 && key > node->right->key)
            return rotateLeft(node);

        // Caso LR
        if (bf > 1 && key > node->left->key) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        // Caso RL
        if (bf < -1 && key < node->right->key) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    // -------------------- Buscar --------------------
    bool search(Node* node, int key) {
        if (node == NULL) return false;
        if (node->key == key) return true;
        if (key < node->key) return search(node->left, key);
        return search(node->right, key);
    }

    // -------------------- Mínimo (para eliminar) --------------------
    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current->left != NULL) current = current->left;
        return current;
    }

    // -------------------- Eliminar --------------------
    Node* remove(Node* node, int key) {
        if (node == NULL) return node;

        if (key < node->key)
            node->left = remove(node->left, key);
        else if (key > node->key)
            node->right = remove(node->right, key);
        else {
            if (node->left == NULL || node->right == NULL) {
                Node* temp = node->left ? node->left : node->right;
                if (temp == NULL) {
                    delete node;
                    return NULL;
                } else {
                    *node = *temp;
                    delete temp;
                }
            } else {
                Node* temp = minValueNode(node->right);
                node->key = temp->key;
                node->right = remove(node->right, temp->key);
            }
        }

        updateHeight(node);

        int bf = balance(node);

        if (bf > 1 && balance(node->left) >= 0)
            return rotateRight(node);
        if (bf > 1 && balance(node->left) < 0) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        if (bf < -1 && balance(node->right) <= 0)
            return rotateLeft(node);
        if (bf < -1 && balance(node->right) > 0) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    // -------------------- Recorrido inorder --------------------
    void inorder(Node* node) {
        if (node == NULL) return;
        inorder(node->left);
        cout << node->key << "(" << node->height << ") ";
        inorder(node->right);
    }

public:
    AVL() { root = NULL; }

    void insert(int key) { root = insert(root, key); }

    void remove(int key) { root = remove(root, key); }

    bool search(int key) { return search(root, key); }

    void displayInorder() {
        inorder(root);
        cout << endl;
    }
};

// -------------------- Main --------------------
int main() {
    AVL avl;

    avl.insert(30);
    avl.insert(20);
    avl.insert(40);
    avl.insert(10);

    cout << "Inorder (valor,altura): ";
    avl.displayInorder();

    avl.remove(20);
    cout << "Inorder tras eliminar 20: ";
    avl.displayInorder();

    return 0;
}
