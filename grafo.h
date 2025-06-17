#ifndef GRAFO_H_INCLUDED
#define GRAFO_H_INCLUDED
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm> // Para std::find

using namespace std;

class Grafo {
private:
    int vertices;
    vector<vector<int>> adj;

    void copiarDesde(const Grafo& otro) {
        vertices = otro.vertices;
        adj = otro.adj;
    }



public:
    Grafo() : vertices(0) {}

    Grafo(int v) : vertices(v), adj(v) {}

    void limpiar() {
        adj.clear();
        vertices = 0;
    }

    // Constructor de copia
    Grafo(const Grafo& otro) {
        copiarDesde(otro);
    }

    // Operador de asignación
    Grafo& operator=(const Grafo& otro) {
        if (this != &otro) {
            limpiar();
            copiarDesde(otro);
        }
        return *this;
    }
    void agregarVertice(int id) {
        if(id>=vertices){
            adj.push_back(vector<int>());
            vertices++;
            cout<<"sale"<<endl;
            cout<<vertices<<endl;
        }

    }

    void agregarArista(int u, int v) {
        if (u >= vertices || v >= vertices) {
            cerr << "Índice de vértice fuera de rango.\n";
            return;
        }

        // Evitar duplicados
        if (find(adj[u].begin(), adj[u].end(), v) == adj[u].end())
            adj[u].push_back(v);

        if (find(adj[v].begin(), adj[v].end(), u) == adj[v].end())
            adj[v].push_back(u);
    }

    void BFS(int inicio) const {
        if (inicio >= vertices) {
            cerr << "Vértice de inicio inválido.\n";
            return;
        }

        vector<bool> visitado(vertices, false);
        queue<int> q;
        visitado[inicio] = true;
        q.push(inicio);

        while (!q.empty()) {
            int nodo = q.front(); q.pop();
            cout << nodo << " ";
            for (int vecino : adj[nodo]) {
                if (!visitado[vecino]) {
                    visitado[vecino] = true;
                    q.push(vecino);
                }
            }
        }
        cout << endl;
    }

    void DFS(int v, vector<bool>& visitado) const {
        visitado[v] = true;
        cout << v << " ";
        for (int vecino : adj[v]) {
            if (!visitado[vecino])
                DFS(vecino, visitado);
        }
    }

    void ejecutarDFS(int inicio) const {
        if (inicio >= vertices) {
            cerr << "Vértice de inicio inválido.\n";
            return;
        }

        vector<bool> visitado(vertices, false);
        DFS(inicio, visitado);
        cout << endl;
    }

    int obtenerVertices() const {
        return vertices;
    }
};



#endif // GRAFO_H_INCLUDED
