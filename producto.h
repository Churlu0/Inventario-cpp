#ifndef PRODUCTO_H_INCLUDED
#define PRODUCTO_H_INCLUDED
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

class Producto {
public:
    string codigo;
    string nombre;
    string categoria;
    int cantidad;
    float precio;

    Producto() : cantidad(0), precio(0.0f) {}

    Producto(string c, string n, string cat, int cant, float p)
        : codigo(c), nombre(n), categoria(cat), cantidad(cant), precio(p) {}
    //regresa el producto como string
    string serializar() const {
        return codigo + "," + nombre + "," + categoria + "," + to_string(cantidad) + "," + to_string(precio);
    }
    //operador menor que
    bool operator<(const Producto& otro) const {
        return nombre < otro.nombre;
    }
    //operador mayor que
    bool operator>(const Producto& otro) const {
        return nombre > otro.nombre;
    }
    //operador igual que
    bool operator==(const Producto& otro) const {
    return nombre == otro.nombre;
    }
    //GET
    double get_precio() const{
        return precio;
    }
    string get_name() const{
        return nombre;
    }
    string get_codigo() const{
        return codigo;
    }
    int get_exist()const{
        return cantidad;
    }
    //SET
    void change_disp(int sub){
        cantidad=cantidad-sub;
    }
    //obtener productos en texto
    static Producto deserializar(const string& linea) {
        stringstream ss(linea);
        string codigo, nombre, categoria, cantidadStr, precioStr;
        getline(ss, codigo, ',');
        getline(ss, nombre, ',');
        getline(ss, categoria, ',');
        getline(ss, cantidadStr, ',');
        getline(ss, precioStr, ',');
        return Producto(codigo, nombre, categoria, stoi(cantidadStr), stof(precioStr));
    }
};
    //operador de muestra de producto(poco usado o sin uso)
    ostream& operator<<(ostream& os, const Producto& p) {
    os << p.get_name();
    return os;
    }


#endif // PRODUCTO_H_INCLUDED
