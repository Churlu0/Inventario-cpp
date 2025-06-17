#ifndef PEDIDO_H_INCLUDED
#define PEDIDO_H_INCLUDED
#include <string>
using namespace std;

class Pedido {
public:
    string codigoProducto;
    int cantidad;
    string direccion;
    //Obtiene el codigo, la cantidad y la direccion
    Pedido() {}

    Pedido(string codigo, int cantidad, string direccion)
        : codigoProducto(codigo), cantidad(cantidad), direccion(direccion) {}
};


#endif // PEDIDO_H_INCLUDED
