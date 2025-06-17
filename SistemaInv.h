#ifndef SISTEMAINV_H_INCLUDED
#define SISTEMAINV_H_INCLUDED

class SistemaInventarios {
private:
    lista_simple<Inventario> tiendas;
    Grafo grafoTiendas;
    int contadorTiendas = 0; // para asignar IDs únicos

public:
    SistemaInventarios() : grafoTiendas(0) {}

    void agregarTienda(const Inventario& nueva) {
        Inventario copia = nueva;
        copia.setId(contadorTiendas); // asignar ID único
        tiendas.push_final(copia);
        grafoTiendas.agregarVertice(contadorTiendas);
        contadorTiendas++;
    }

    void conectarTiendas(int id1, int id2) {
        grafoTiendas.agregarArista(id1, id2);
    }

    void mostrarRutasDesde(int idTienda) {
        cout << "Rutas desde tienda " << idTienda << " (BFS): ";
        grafoTiendas.BFS(idTienda);
        cout << endl;
    }

    Inventario& obtenerTienda(int id) {
        for (int i = 0; i < tiendas.size(); ++i) {
            if (tiendas.get(i).getId() == id)
                return tiendas.get_ref(i);
        }
        throw runtime_error("ID de tienda no encontrado.");
    }

    int totalTiendas() const {
        return tiendas.size();
    }
};

#endif // SISTEMAINV_H_INCLUDED
