#ifndef PILA_H_INCLUDED
#define PILA_H_INCLUDED
#include <iostream>
#include <string>
#include<cstring>
#include <utility>
#include"lista_doble.h"
using namespace std;


template <typename tipo>

class pila
{
public:
    pila()
    {
        head=nullptr;
        tail=nullptr;
        longitud=0;
    }
    pila(const pila& otra) : head(nullptr), longitud(0) {
        copiarDesde(otra);
    }

    // Operador de asignación
    pila& operator=(const pila& otra) {
        if (this != &otra) {
            liberar();
            copiarDesde(otra);
        }
        return *this;
    }
    pila(pila &&rhs)
    {
        head=move(rhs.head);
        tail=move(rhs.tail);
        longitud=move(rhs.longitud);
    }
    ~pila()
    {
        if(head!=nullptr)
        delete head;
        if(tail!=nullptr&&longitud>1)
        delete tail;
    }
    int vacia() const
    {
        if(head==nullptr)
            return 1;
        else
            return 0;
    }
    void push(tipo valor)
    {
        nodo<tipo> *nuevo = new nodo<tipo>(valor);
        if(vacia()) {
        head = tail = nuevo;
        nuevo->next = nullptr;
        nuevo->prev = nullptr;
        longitud++;
        }
        else
        {
            nuevo->next=head;
            head->prev=nuevo;
            head=nuevo;
            head->prev=nullptr;
            tail->next=nullptr;
            longitud++;

        }
    }

    tipo pop() {
    if (vacia()) {
        throw std::out_of_range("pila vacía");
    }
    nodo<tipo>* tmp = head;
    tipo valor = tmp->data;
    head = head->next;
    delete tmp;
    longitud--;
    return valor;
}

    tipo get(int i)
    {
        nodo<tipo> *tmp=head;
        if(!vacia())
        {
            if(i==1)
            {
                return tmp->data;
            }
            else if(i==longitud)
            {
                return tail->data;
            }
            else
            {
                for(int j=1;j<i;j++)
                tmp=tmp->next;
                return tmp->data;

            }
        }
        else
        {
            throw std::out_of_range("Índice fuera de rango o lista vacía");
        }
    }
    int get_longitud()
    {
        return longitud;
    }
    nodo<tipo>* recorrer(int k) const{
        nodo<tipo>*tmp=nullptr;
        if(!vacia()){
         tmp=head;
        for(int j=1;j<k;j++)
            tmp=tmp->next;
        }else
            return nullptr;
        return tmp;
    }
    nodo<tipo>* get_head(){
        return head;
    }
    nodo<tipo>* get_tail(){
        return tail;
        }
    tipo top() const {
    if (!vacia()) return head->data;
    throw std::out_of_range("Pila vacía");
}
private:

    nodo<tipo> *head;
    nodo<tipo> *tail;
    int longitud;
     void copiarDesde(const pila& otra) {


    if (otra.vacia()) {

        return;
    }

    nodo<tipo>* actual = otra.head;
    pila<tipo> temp;



    while (actual != nullptr) {
        temp.push(actual->data);

        actual = actual->next;
    }



    while (!temp.vacia()) {
        tipo val = temp.pop();
        push(val);

    }


}

    void liberar() {
        while (!vacia()) {
            pop();
        }
    }
};


#endif // PILA_H_INCLUDED
