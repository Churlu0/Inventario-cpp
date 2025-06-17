#ifndef OPERACION_H_INCLUDED
#define OPERACION_H_INCLUDED
#include "producto.h"
//Declaracion de un tipo no una variable global!!!!
enum TipoOperacion { AGREGAR, ELIMINAR, MODIFICAR };
//Registra un tipo para saber cual será su contraria
class Operacion {
public:
    TipoOperacion tipo;
    Producto productoAntes;
    Producto productoDespues;

    Operacion() {}

    Operacion(TipoOperacion t, const Producto& a, const Producto& d)
        : tipo(t), productoAntes(a), productoDespues(d) {}
};


#endif // OPERACION_H_INCLUDED
