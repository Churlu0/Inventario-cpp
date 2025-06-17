#ifndef SERIALIZADOR_H_INCLUDED
#define SERIALIZADOR_H_INCLUDED
#include "producto.h"
#include "lista_doble.h"
#include <fstream>
using namespace std;
class Serializador {
public:
    static void guardarProductos(const lista_doble<Producto>& productos, const string& archivo) {
        //tomar una ruta para escribir en un fichero
        ofstream out(archivo);
        //Cantidad de productos
        int longitud=productos.get_longitud();
        for (int i = 1; i < longitud+1; ++i) {
            //Escritura dentro del  fichero
            out << productos.get(i).serializar() << endl;
        }

        out.close();
    }

    static void cargarProductos(lista_doble<Producto>& productos, const string& archivo) {
        //Leer del archivo
        ifstream in(archivo);
        string linea;
        while (getline(in, linea)) {

            if (linea.empty() || linea.find_first_not_of(" \t\r\n") == std::string::npos) {
                continue; // Ignora líneas vacías o solo con espacios
            }
            //obtiene datos deserializados y los agrega a productos
            Producto p = Producto::deserializar(linea);
            productos.push_final(p);
        }
        in.close();
    }
};


#endif // SERIALIZADOR_H_INCLUDED
