#ifndef COLA_H_INCLUDED
#define COLA_H_INCLUDED
#include <iostream>
#include <string>
#include<cstring>
#include <utility>
#include"lista_doble.h"
using namespace std;


template <typename tipo>

class cola
{
public:
    cola()
    {
        head=nullptr;
        tail=nullptr;
        longitud=0;
    }
    cola(const cola& otra) : head(nullptr), longitud(0) {
        copiarDesde(otra);
    }
    cola(cola &&rhs)
    {
        head=move(rhs.head);
        tail=move(rhs.tail);
        longitud=move(rhs.longitud);
    }
    cola& operator=(const cola& otra) {
        if (this != &otra) {
            liberar();
            copiarDesde(otra);
        }
        return *this;
    }
    ~cola()
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
    void enqueue(tipo valor)
    {
        nodo<tipo> *nuevo = new nodo<tipo>(valor);
        if(vacia()) {
        head = tail = nuevo;
        nuevo->next = nullptr;
        nuevo->prev = nullptr;
        longitud++;
        }
        else if(head==tail)
        {
            head->next=nuevo;
            tail=nuevo;
            tail->prev=head;
            tail->next=head;
            head->prev=tail;
            longitud++;

        }

        else
        {
            nuevo->prev=tail;
            tail->next=nuevo;
            tail=nuevo;
            tail->next=head;
            head->prev=tail;
            longitud++;

        }

    }
    tipo dequeue() {
    if (vacia()) {
        throw std::out_of_range("lista vacía");
    }

    nodo<tipo>* tmp = head;
    tipo valor = tmp->data;

    if (longitud == 1) {
        head = tail = nullptr;
    } else {
        head = head->next;
        head->prev = tail;
        tail->next = head;
    }

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
    nodo<tipo>* get_head(){
        return head;
    }
    nodo<tipo>* get_tail(){
        return tail;
    }
private:

    nodo<tipo> *head;
    nodo<tipo> *tail;
    int longitud;
    void copiarDesde(const cola& otra) {


    if (otra.vacia()) {

        return;
    }

    nodo<tipo>* actual = otra.head;
    cola<tipo> temp;



    while (actual != nullptr) {
        temp.enqueue(actual->data);

        actual = actual->next;
    }



    while (!temp.vacia()) {
        tipo val = temp.dequeue();
        enqueue(val);

    }


}
    void liberar() {
        while (!vacia()) {
            dequeue();
        }
    }
};


#endif // COLA_H_INCLUDED
