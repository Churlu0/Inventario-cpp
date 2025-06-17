#ifndef INVENTARIO_H_INCLUDED
#define INVENTARIO_H_INCLUDED
#include "lista_doble.h"
#include "producto.h"
#include "Operacion.h"
#include "Pedido.h"
#include "pila.h"
#include "cola.h"
#include "grafo.h"
#include "arbol_binario.h"
#include "avl.h"
#include "serializador.h"
#include <algorithm>
#include <map>

class Inventario {
private:
    Grafo redDistribucion;
    lista_doble<Producto> productos;
    pila<Operacion> historial;
    pila<Operacion> deshacer;
    cola<Pedido> pedidos;
    ArbolBinario<Producto> arbolBusqueda;
    AVL<Producto> arbolBalanceado;
    lista_doble<int> disponibilidad;
    lista_doble<std::array<int, 12>> ventas;
    int id;

public:
    Inventario() : redDistribucion(0) {}
    //constructor copia
    Inventario(const Inventario& otro) {
    productos = otro.productos;
    historial = otro.historial;
    deshacer = otro.deshacer;
    pedidos = otro.pedidos;
    arbolBusqueda = otro.arbolBusqueda;
    arbolBalanceado = otro.arbolBalanceado;
    disponibilidad = otro.disponibilidad;
    ventas = otro.ventas;
    id = otro.getId();
}
    //constructor operador asignacion
    Inventario& operator=(const Inventario& otro) {
    if (this != &otro) {
        productos = otro.productos;
        historial = otro.historial;
        deshacer = otro.deshacer;
        pedidos = otro.pedidos;
        arbolBusqueda = otro.arbolBusqueda;
        arbolBalanceado = otro.arbolBalanceado;
        disponibilidad = otro.disponibilidad;
        ventas = otro.ventas;

        id = otro.getId();
    }
    return *this;
}
    //Set id unico por tienda
    void setId(int nuevoId) { id = nuevoId; }
    int getId() const { return id; }

    ArbolBinario<Producto>& getBST() { return arbolBusqueda; }
    AVL<Producto>& getAVL() { return arbolBalanceado; }

    //Busqueda de elementos en archivo
    void cargarDesdeArchivo(const string& ruta) {
    productos.clear();  // Asegurar limpieza
    disponibilidad.clear();
    ventas.clear();
    arbolBusqueda.vaciar();
    arbolBalanceado.vaciar();


    Serializador::cargarProductos(productos, ruta);
    for (int i = 1; i <= productos.get_longitud(); ++i) {
        std::array<int, 12> vacio = {0};
        Producto p = productos.get(i);
        arbolBusqueda.insertar(p);
        arbolBalanceado.insertar(p);
        disponibilidad.push_final(p.cantidad);
        ventas.push_final(vacio);
    }
}
    //Escritura en archivo para persistencia
    void guardarEnArchivo(const string& ruta) {
        if (productos.vacia()) {
        cout << "[guardarEnArchivo] No hay productos que guardar.\n";
        return;
        }
        Serializador::guardarProductos(productos, ruta);
    }
    //Codigo unico con base a la categoria
    string generarCodigoProducto(const string& categoria) {
    char inicial = toupper(categoria[0]);
    int contador = 0;//contador de productos de la misma categoria
    //busqueda de previos productos en la misma categoria
    for (int i = 1; i <= productos.get_longitud(); ++i) {
        Producto p = productos.get(i);
        if (!p.codigo.empty() && p.codigo[0] == inicial) {
            contador++;
        }
    }
    //Genera el codigo en bbase a el contador y la categoria
    char buffer[10];
    snprintf(buffer, sizeof(buffer), "%c%03d", inicial, contador + 1);
    return string(buffer);
}

    void agregarProducto(const Producto& p, bool registrar = true) {
        //Se agrega a las estructuras
        productos.push_final(p);
        disponibilidad.push_final(p.cantidad);
        std::array<int, 12> vacio = {0};
        ventas.push_final(vacio);
        //Se agrega al historial
        if (registrar) {
        historial.push(Operacion(AGREGAR, Producto(),p));
        }
        arbolBusqueda.insertar(p);
        arbolBalanceado.insertar(p);
        while (!deshacer.vacia()) deshacer.pop();
    }

    void eliminarProducto(const string& codigo, bool registrar = true) {
    //Busqueda
    for (int i = 1; i < productos.get_longitud()+1; ++i) {
        if (productos.get(i).codigo == codigo) {
            const Producto eliminado =  productos.get(i);
            productos.eliminar(i);
            disponibilidad.eliminar(i);
            ventas.eliminar(i);
            arbolBalanceado.eliminar(eliminado);
            arbolBusqueda.eliminar(eliminado);
            //Registrar evento en historial
            if (registrar) {

                historial.push(Operacion(ELIMINAR, eliminado, Producto()));
            }
            break;
        }
    }

}
    void modificarProducto(const string& codigo, const Producto& nuevo, bool registrar = true) {
        for (int i = 1; i < productos.get_longitud()+1; ++i) {
            if (productos.get(i).codigo == codigo) {
                Producto anterior = productos.get(i);
                productos.setDato(i, nuevo);
                historial.push(Operacion(MODIFICAR, anterior, nuevo));
                for (int i = 0; i < productos.get_longitud(); ++i) {
                    if (productos.get(i).codigo == nuevo.codigo) {
                    disponibilidad.setDato(i, nuevo.cantidad);
                        break;
                    }
                }
                while (!deshacer.vacia()) deshacer.pop();
                return;
            }
            if (registrar) {
                historial.push(Operacion(MODIFICAR, Producto(), nuevo));
            }
        }
    }
    int obtenerDisponibilidad(const string& codigo) {
        for (int i = 1; i < productos.get_longitud()+1; ++i) {
            if (productos.get(i).codigo == codigo)
                return disponibilidad.get(i);
        }
        return 0;
    }
    int obtenerVentas(const string& codigo, int mes) {
        for (int i = 1; i < productos.get_longitud()+1; ++i) {
            if (productos.get(i).codigo == codigo)
                return ventas.get(i)[mes];
        }
        return 0;
    }
    void registrarVenta(const string& codigo, int cantidad, int mes) {
        for (int i = 1; i < productos.get_longitud()+1; ++i) {
            if (productos.get(i).codigo == codigo) {
                int nuevoStock = disponibilidad.get(i) - cantidad;
                disponibilidad.setDato(i, nuevoStock);
                ventas.get(i)[mes] += cantidad;
                return;
            }
        }
    }

    void undo() {

    if (!historial.vacia()) {

        Operacion op = historial.pop();
        //Se aplica la operacion contraria para lograr el undo
        switch(op.tipo){
        case AGREGAR:
            eliminarProducto(op.productoDespues.codigo, false);
            break;
        case ELIMINAR:
            agregarProducto(op.productoAntes, false);
            break;
        case MODIFICAR:
            modificarProducto(op.productoAntes.codigo, op.productoAntes, false);
            break;
        }

        deshacer.push(op);
    }
}

    void redo() {

        if (deshacer.vacia()) return;

        Operacion op = deshacer.top();
        deshacer.pop();
        historial.push(op);
        //Se aplica la operacion contraria para lograr el redo
        switch (op.tipo) {
            case AGREGAR:

                agregarProducto(op.productoDespues);
                break;
            case ELIMINAR:

                eliminarProducto(op.productoAntes.codigo);
                break;
            case MODIFICAR:

                modificarProducto(op.productoAntes.codigo, op.productoDespues);
                break;
        }
    }
    //Encolamiento de pedidos
    void agregarPedido(const Pedido& p) {
        pedidos.enqueue(p);
    }
    //Registra el pedido en ventas y disponibilidad y lo saca de la cola
    void procesarPedido() {
    if (!pedidos.vacia()) {
        Pedido p = pedidos.dequeue();

        for (int i = 1; i < productos.get_longitud()+1; ++i) {
            if (productos.get(i).codigo == p.codigoProducto) {
                // Actualizar disponibilidad
                int actual = disponibilidad.get(i);
                disponibilidad.setDato(i, actual - p.cantidad);
                Producto& prod = productos.get_tipo(i)->data;
                prod.change_disp(p.cantidad);
                // Actualizar ventas
                std::array<int, 12> registro = ventas.get(i);
                registro[0] += p.cantidad; // mes 0 como ejemplo
                ventas.setDato(i, registro);
                break;
            }
        }
    }
}
    //(SIN USO)
    Producto* buscarPorCodigo(const string& codigo) {
        for (int i = 1; i < productos.get_longitud()+1; ++i) {
            if (productos.get(i).codigo == codigo) {
                Producto ret = productos.get(i);
                return &ret;
            }
        }
        return nullptr;
    }

    Producto* buscarPorNombre(const string& nombre) {
        for (int i = 1; i < productos.get_longitud()+1; ++i) {
            if (productos.get(i).nombre == nombre) {
                Producto ret = productos.get(i);
                return &ret;
            }
        }
        return nullptr;
    }
    bool buscarProductoPorNombreArb(string& nombre) {
        Producto temp("", nombre, "", 0, 0.0);
        return arbolBusqueda.buscar(temp);
    }
    void mostrarProductosOrdenados() {
        arbolBalanceado.inOrden();
    }

    void ordenarPorNombre() {
        productos.ordenar([](const Producto& a, const Producto& b) {
            return a.nombre < b.nombre;
        });
    }

    void ordenarPorPrecio() {
        productos.ordenar([](const Producto& a, const Producto& b) {
            return a.precio < b.precio;
        });
    }





    lista_doble<Producto>& getProductos() {

        return productos;
    }

};

#endif // INVENTARIO_H_INCLUDED
