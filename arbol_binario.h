#ifndef ARBOL_BINARIO_H_INCLUDED
#define ARBOL_BINARIO_H_INCLUDED
#include <iostream>
#include <string>
using namespace std;

template <typename T>
struct NodoArbol {
    T dato;
    NodoArbol* izq;
    NodoArbol* der;
    NodoArbol(T d) : dato(d), izq(nullptr), der(nullptr) {}
};

template <typename T>
class ArbolBinario {
public:
    NodoArbol<T>* raiz;

    ArbolBinario() : raiz(nullptr) {}
    //Copia
    ArbolBinario(const ArbolBinario& otro) {
    raiz = copiar(otro.raiz);
    }
    //Asignacion
    ArbolBinario& operator=(const ArbolBinario& otro) {
    if (this != &otro) {
        liberar(raiz);
        raiz = copiar(otro.raiz);
    }
    return *this;
    }

    void insertar(T valor) {
        raiz = insertarRec(raiz, valor);
    }

    bool buscar(const T& valor) {
        return buscarRec(raiz, valor);
    }

    void enOrden() {
        enOrdenRec(raiz);
    }
    void vaciar() {
    vaciarNodo(raiz);
    raiz = nullptr;
    }

    void vaciarNodo(NodoArbol<T>* nodo) {
    if (nodo == nullptr) return;
    vaciarNodo(nodo->izq);
    vaciarNodo(nodo->der);
    delete nodo;
    }
    void eliminar(const T& valor) {
    raiz = eliminarRec(raiz, valor);
    }

private:
    NodoArbol<T>* insertarRec(NodoArbol<T>* nodo, T valor) {
        if (!nodo) return new NodoArbol<T>(valor);
        //verificar antes de insertar para tener la posicion
        if (valor.nombre < nodo->dato.nombre)
            nodo->izq = insertarRec(nodo->izq, valor);
        else
            nodo->der = insertarRec(nodo->der, valor);
        return nodo;
    }
    void liberar(NodoArbol<T>* nodo) {
        if (nodo) {
            liberar(nodo->izq);
            liberar(nodo->der);
            delete nodo;
        }
    }


    NodoArbol<T>* copiar(NodoArbol<T>* nodo) {
    //obtener desde nodo datos a copiar
    if (!nodo) return nullptr;
    NodoArbol<T>* nuevo = new NodoArbol<T>(nodo->dato);
    nuevo->izq = copiar(nodo->izq);
    nuevo->der = copiar(nodo->der);
    return nuevo;
    }

    bool buscarRec(NodoArbol<T>* nodo, const T& valor) {
        if (!nodo) return false;
        if (valor.nombre == nodo->dato.nombre) return true;
        if (valor.nombre < nodo->dato.nombre)
            return buscarRec(nodo->izq, valor);
        else
            return buscarRec(nodo->der, valor);
    }

    void enOrdenRec(NodoArbol<T>* nodo) {
        if (!nodo) return;
        enOrdenRec(nodo->izq);
        cout << nodo->dato.codigo << " - " << nodo->dato.nombre << endl;
        enOrdenRec(nodo->der);
    }
    NodoArbol<T>* eliminarRec(NodoArbol<T>* nodo, const T& valor) {
    if (!nodo) return nullptr;

    if (valor.nombre < nodo->dato.nombre) {
        nodo->izq = eliminarRec(nodo->izq, valor);
    } else if (valor.nombre > nodo->dato.nombre) {
        nodo->der = eliminarRec(nodo->der, valor);
    } else {
        // Nodo con solo un hijo o sin hijos
        if (!nodo->izq) {
            NodoArbol<T>* temp = nodo->der;
            delete nodo;
            return temp;
        } else if (!nodo->der) {
            NodoArbol<T>* temp = nodo->izq;
            delete nodo;
            return temp;
        }

        // Nodo con dos hijos: obtener el menor en la rama derecha
        NodoArbol<T>* temp = minimoNodo(nodo->der);
        nodo->dato = temp->dato;
        nodo->der = eliminarRec(nodo->der, temp->dato);
    }

    return nodo;
}

NodoArbol<T>* minimoNodo(NodoArbol<T>* nodo) {
    NodoArbol<T>* actual = nodo;
    while (actual && actual->izq)
        actual = actual->izq;
    return actual;
}
};


#endif // ARBOL_BINARIO_H_INCLUDED
