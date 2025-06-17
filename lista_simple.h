#ifndef LISTA_SIMPLE_H_INCLUDED
#define LISTA_SIMPLE_H_INCLUDED
template <typename T>
class NodoSimple {
public:
    T data;
    NodoSimple* next;

    NodoSimple(T val) : data(val), next(nullptr) {}
};

template <typename T>
class lista_simple {
private:
    NodoSimple<T>* head;
    NodoSimple<T>* tail;
    int longitud;

public:
    lista_simple() : head(nullptr),tail(nullptr), longitud(0) {}

    void push(T valor) {
        NodoSimple<T>* nuevo = new NodoSimple<T>(valor);
        if (!head) {
            head = nuevo;
            tail = nuevo;
        } else {
            NodoSimple<T>* temp = head;
            while (temp->next) temp = temp->next;
            temp->next = nuevo;
            tail = nuevo;
        }
        longitud++;
    }
    void push_final(const T& valor) {


    NodoSimple<T>* nuevo = new NodoSimple<T>(valor);

    if (head == nullptr) {

        head = tail = nuevo;
    } else {

        tail->next = nuevo;
        tail = nuevo;
    }

    longitud++;
}
    //Obtener una copia de elemento
    T get(int index) {

        NodoSimple<T>* temp = head;
        for (int i = 0; i < index && temp; ++i)
            temp = temp->next;
        if (temp) return temp->data;
        throw out_of_range("Índice fuera de rango");
    }
    //Obtener una referencia para modificar
    T& get_ref(int index) {
        NodoSimple<T>* nodo_encontrado = head;
        for (int i = 0; i < index && nodo_encontrado; ++i)
            nodo_encontrado= nodo_encontrado->next;
        if (nodo_encontrado) return nodo_encontrado->data;;
        throw out_of_range("Índice fuera de rango");


}

    int size() const { return longitud; }

    NodoSimple<T>* get_head() { return head; }
};



#endif // LISTA_SIMPLE_H_INCLUDED
