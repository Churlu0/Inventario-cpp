#ifndef AVL_H_INCLUDED
#define AVL_H_INCLUDED
template <typename T>
class NodoAVL {
public:
    T data;
    int altura;
    NodoAVL* izquierda;
    NodoAVL* derecha;

    NodoAVL(T val) : data(val), altura(1), izquierda(nullptr), derecha(nullptr) {}
};

template <typename T>
class AVL {
private:
    NodoAVL<T>* raiz;

    int altura(NodoAVL<T>* n) {
        return n ? n->altura : 0;
    }
    void liberar(NodoAVL<T>* nodo) {
        if (nodo) {
            liberar(nodo->izquierda);
            liberar(nodo->derecha);

            delete nodo;
        }
    }

    NodoAVL<T>* copiar(NodoAVL<T>* nodo) {
    if (!nodo) return nullptr;
    NodoAVL<T>* nuevo = new NodoAVL<T>(nodo->data);
    nuevo->izquierda = copiar(nodo->izquierda);
    nuevo->derecha = copiar(nodo->derecha);
    return nuevo;
}

    int balance(NodoAVL<T>* n) {
        return n ? altura(n->izquierda) - altura(n->derecha) : 0;
    }

    NodoAVL<T>* rotarDerecha(NodoAVL<T>* y) {
        NodoAVL<T>* x = y->izquierda;
        NodoAVL<T>* T2 = x->derecha;

        x->derecha = y;
        y->izquierda = T2;

        y->altura = max(altura(y->izquierda), altura(y->derecha)) + 1;
        x->altura = max(altura(x->izquierda), altura(x->derecha)) + 1;

        return x;
    }

    NodoAVL<T>* rotarIzquierda(NodoAVL<T>* x) {
        NodoAVL<T>* y = x->derecha;
        NodoAVL<T>* T2 = y->izquierda;

        y->izquierda = x;
        x->derecha = T2;

        x->altura = max(altura(x->izquierda), altura(x->derecha)) + 1;
        y->altura = max(altura(y->izquierda), altura(y->derecha)) + 1;

        return y;
    }

    NodoAVL<T>* insertar(NodoAVL<T>* nodo, T val) {
        if (!nodo) return new NodoAVL<T>(val);
        if (val < nodo->data)
            nodo->izquierda = insertar(nodo->izquierda, val);
        else
            nodo->derecha = insertar(nodo->derecha, val);

        nodo->altura = max(altura(nodo->izquierda), altura(nodo->derecha)) + 1;
        int balanceFactor = balance(nodo);

        // Rotaciones
        if (balanceFactor > 1 && val < nodo->izquierda->data)
            return rotarDerecha(nodo);
        if (balanceFactor < -1 && val > nodo->derecha->data)
            return rotarIzquierda(nodo);
        if (balanceFactor > 1 && val > nodo->izquierda->data) {
            nodo->izquierda = rotarIzquierda(nodo->izquierda);
            return rotarDerecha(nodo);
        }
        if (balanceFactor < -1 && val < nodo->derecha->data) {
            nodo->derecha = rotarDerecha(nodo->derecha);
            return rotarIzquierda(nodo);
        }

        return nodo;
    }
    NodoAVL<T>* eliminarRec(NodoAVL<T>* nodo, T val) {
    if (!nodo) return nodo;

    if (val < nodo->data)
        nodo->izquierda = eliminarRec(nodo->izquierda, val);
    else if (val > nodo->data)
        nodo->derecha = eliminarRec(nodo->derecha, val);
    else {
        // Nodo con un hijo o sin hijos
        if (!nodo->izquierda || !nodo->derecha) {
            NodoAVL<T>* temp = nodo->izquierda ? nodo->izquierda : nodo->derecha;
            delete nodo;
            return temp;
        }

        // Nodo con dos hijos: obtener el menor de la derecha
        NodoAVL<T>* temp = nodoMinimo(nodo->derecha);
        nodo->data = temp->data;
        nodo->derecha = eliminarRec(nodo->derecha, temp->data);
    }

    // Actualizar altura y balancear
    nodo->altura = max(altura(nodo->izquierda), altura(nodo->derecha)) + 1;
    int balanceFactor = balance(nodo);

    // Rotaciones
    if (balanceFactor > 1 && balance(nodo->izquierda) >= 0)
        return rotarDerecha(nodo);
    if (balanceFactor > 1 && balance(nodo->izquierda) < 0) {
        nodo->izquierda = rotarIzquierda(nodo->izquierda);
        return rotarDerecha(nodo);
    }
    if (balanceFactor < -1 && balance(nodo->derecha) <= 0)
        return rotarIzquierda(nodo);
    if (balanceFactor < -1 && balance(nodo->derecha) > 0) {
        nodo->derecha = rotarDerecha(nodo->derecha);
        return rotarIzquierda(nodo);
    }

    return nodo;
}

NodoAVL<T>* nodoMinimo(NodoAVL<T>* nodo) {
    NodoAVL<T>* actual = nodo;
    while (actual->izquierda)
        actual = actual->izquierda;
    return actual;
}


public:
    AVL() : raiz(nullptr) {}

    AVL(const AVL& otro) {
        raiz = copiar(otro.raiz);
    }

    AVL& operator=(const AVL& otro) {
        if (this != &otro) {
            liberar(raiz);
            raiz = copiar(otro.raiz);
        }
        return *this;
    }

    ~AVL() {
        liberar(raiz);
    }

    void insertar(T val) {
        raiz = insertar(raiz, val);
    }
    void vaciar() {
    vaciarNodo(raiz);
    raiz = nullptr;
}

void vaciarNodo(NodoAVL<T>* nodo) {
    if (nodo == nullptr) return;
    vaciarNodo(nodo->izquierda);
    vaciarNodo(nodo->derecha);
    delete nodo;
}
// Inorden: izquierda, raíz, derecha
void inOrden() const {
    inOrdenRec(raiz);
    cout << endl;
}

void inOrdenRec(NodoAVL<T>* nodo) const {
    if (nodo == nullptr) return;
    inOrdenRec(nodo->izquierda);
    cout << nodo->data <<endl;
    inOrdenRec(nodo->derecha);
}

// Preorden: raíz, izquierda, derecha
void preOrden() const {
    preOrdenRec(raiz);
    cout << endl;
}

void preOrdenRec(NodoAVL<T>* nodo) const {
    if (nodo == nullptr) return;
    cout << nodo->data << " ";
    preOrdenRec(nodo->izquierda);
    preOrdenRec(nodo->derecha);
}

// Postorden: izquierda, derecha, raíz
void postOrden() const {
    postOrdenRec(raiz);
    cout << endl;
}

void postOrdenRec(NodoAVL<T>* nodo) const {
    if (nodo == nullptr) return;
    postOrdenRec(nodo->izquierda);
    postOrdenRec(nodo->derecha);
    cout << nodo->data << " ";
}
void eliminar(T val) {
    raiz = eliminarRec(raiz, val);
}

};


#endif // AVL_H_INCLUDED
