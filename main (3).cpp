#include <iostream>
#include "inventario.h"
#include "lista_simple.h"
#include "Sistemainv.h"
#include "menu.h"
#include <chrono>
using namespace std::chrono;
using namespace std;
void menu(string opc, SistemaInventarios* sistema){
    int tienda;
    if(opc=="1"){
        Inventario tiendai;
        tiendai.cargarDesdeArchivo("productos.txt");
        sistema->agregarTienda(tiendai);
        int total = sistema->totalTiendas();
        if (total >= 2) {
            int idAnterior = sistema->obtenerTienda(total - 2).getId();
            int idActual = sistema->obtenerTienda(total - 1).getId();
            sistema->conectarTiendas(idAnterior, idActual);
        }
    }else if(opc=="2"){
        string nombre, categoria, codigo;
        double precio;
        int existencia;
        cout<<"A que tienda desea agreggar el producto?"<<endl;
        cout<<"0-"<<sistema->totalTiendas()-1<<endl;
        cin>>tienda;
        if(tienda>=0&& tienda<=sistema->totalTiendas()&&sistema->totalTiendas()!=0){
            cout<<"nombre"<<endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, nombre);
            cout<<"categoria"<<endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, categoria);
            cout<<"precio"<<endl;
            cin>>precio;
            cout<<"existencias"<<endl;
            cin>>existencia;
            codigo=sistema->obtenerTienda(tienda).generarCodigoProducto(categoria);
            Producto producto(codigo,nombre,categoria,existencia,precio);
            sistema->obtenerTienda(tienda).agregarProducto(producto);
        }
        else cout<<"Opcion no valida"<<endl;

    }
    else if(opc=="3"){
        string codigo, direccion;
        int cantidad;
        cout<<"En que tienda desea hacer esto"<<endl;
        cout<<"0-"<<sistema->totalTiendas()-1<<endl;
        cin>>tienda;
        if(tienda>=0&& tienda<=sistema->totalTiendas()&&sistema->totalTiendas()!=0){
            cout<<"Ingrese el codigo de producto:"<<endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin>>codigo;

            cout<<"Ingrese la cantidad a ordenar:"<<endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin>>cantidad;

            cout<<"Ingrese la direccion a entregar:"<<endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, direccion);

            Pedido p(codigo, cantidad, direccion);
            sistema->obtenerTienda(tienda).agregarPedido(p);
            cout<<"Pedido agregado con exito"<<endl;
        }
        else cout<<"Opcion no valida"<<endl;



    }
    else if(opc=="4"){
        cout<<"En que tienda desea hacer esto"<<endl;
        cout<<"0-"<<sistema->totalTiendas()-1<<endl;
        cin>>tienda;
        if(tienda>=0&& tienda<=sistema->totalTiendas()&&sistema->totalTiendas()!=0)
            sistema->obtenerTienda(tienda).procesarPedido();


    }
    else if(opc=="5"){
        cout<<"En que tienda desea hacer undo"<<endl;
        cout<<"0-"<<sistema->totalTiendas()-1<<endl;
        cin>>tienda;
        if(tienda>=0&& tienda<=sistema->totalTiendas()&&sistema->totalTiendas()!=0)
            sistema->obtenerTienda(tienda).undo();
    }
    else if(opc=="6"){
        cout<<"En que tienda desea hacer redo"<<endl;
        cout<<"0-"<<sistema->totalTiendas()-1<<endl;
        cin>>tienda;
        if(tienda>=0&& tienda<=sistema->totalTiendas()&&sistema->totalTiendas()!=0)
            sistema->obtenerTienda(tienda).redo();
    }
    else if(opc=="7"){
        string nombre;
        cout<<"En que tienda desea hacer esto"<<endl;
        cout<<"0-"<<sistema->totalTiendas()-1<<endl;
        cin>>tienda;
        if(tienda>=0&& tienda<=sistema->totalTiendas()&&sistema->totalTiendas()!=0){
        cout<<"Ingrese el nombre del producto"<<endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, nombre);
        if(sistema->obtenerTienda(tienda).buscarProductoPorNombreArb(nombre))cout<<"Encontrado"<<endl;
        }
    }
    else if(opc=="8"){
        cout<<"En que tienda desea hacer esto"<<endl;
        cout<<"0-"<<sistema->totalTiendas()-1<<endl;
        cin>>tienda;
        if(tienda>=0&& tienda<=sistema->totalTiendas()&&sistema->totalTiendas()!=0)
            sistema->obtenerTienda(tienda).mostrarProductosOrdenados();

    }
    else if(opc=="9"){
            for(int k=0;k<sistema->totalTiendas();k++){
                sistema->mostrarRutasDesde(k);
            }

    }
    else if(opc=="10"){

        for(int k=0; k<sistema->totalTiendas();k++){
            cout<<"Tienda: "<<k<<endl;
            for(int a=1; a<=sistema->obtenerTienda(k).getProductos().get_longitud(); a++){
                Producto p=sistema->obtenerTienda(k).getProductos().get(a);
                cout<<"Nombre: "<<p.get_name()<<"| Codigo: "<<p.get_codigo()<<endl;
                cout<<"Precio: "<<p.get_precio()<<"| Existencia: "<<p.get_exist()<<endl;
            }
        }
    }else if (opc == "12") {
    int tienda;
    string nombre;

    cout << "En qué tienda desea hacer esto" << endl;
    cout << "0-" << sistema->totalTiendas() - 1 << endl;
    cin >> tienda;


    if (tienda >= 0 && tienda < sistema->totalTiendas() && sistema->totalTiendas() != 0) {
        cout << "Ingrese el nombre del producto" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, nombre);

        auto inicio1 = high_resolution_clock::now();
        volatile bool find1;
        for (int i = 0; i < 1000; ++i) {
            find1= sistema->obtenerTienda(tienda).buscarProductoPorNombreArb(nombre);
        }

        auto fin1 = high_resolution_clock::now();
        auto duracion1 = duration_cast<nanoseconds>(fin1 - inicio1);

        auto inicio2 = high_resolution_clock::now();
        volatile bool find2;
        for (int i = 0; i < 1000; ++i) {
            find2= sistema->obtenerTienda(tienda).buscarPorNombre(nombre);
        }
        auto fin2 = high_resolution_clock::now();
        auto duracion2 = duration_cast<nanoseconds>(fin2 - inicio2);

        std::cout << "Tiempo de búsqueda (Árbol binario): " << duracion1.count() << " ns\n";
        std::cout << "Tiempo de búsqueda (Lista doble): " << duracion2.count() << " ns\n";

        if (find1 || find2)
            std::cout << "Producto encontrado.\n";
        else
            std::cout << "Producto no encontrado.\n";
    } else {
        cout << "Tienda inválida o no existen tiendas.\n";
    }
}
    else{
        cout<<"Saliendo....."<<endl;
    }
}
int main() {
SistemaInventarios* sistema2= new SistemaInventarios();
bool exit = true;
string opc;

do{
    cout<<"--------------Menu Inventario--------------"<<endl;
    cout<<"1.-Agregar inventario"<<endl;
    cout<<"2.-Agregar producto a inventario"<<endl;
    cout<<"3.-Pedido"<<endl;
    cout<<"4.-Procesar pedido"<<endl;
    cout<<"5.-Undo"<<endl;
    cout<<"6.-Redo"<<endl;
    cout<<"7.-Busqueda por nombre"<<endl;
    cout<<"8.-Ordenamiento por AVL"<<endl;
    cout<<"9.-Mostrar conexion entre tiendas"<<endl;
    cout<<"10.-Mostrar productos en tiendas"<<endl;
    cout<<"11.-Salir"<<endl;
    cout<<"EXTRAS"<<endl;
    cout<<"12.-Medir eficiencia de busqueda"<<endl;
    cout<<"--------------Menu Inventario--------------"<<endl;
    cin>>opc;
    menu(opc, sistema2);
    if(opc=="11"||opc<="0")exit=false;
    system("pause");
    system("cls");


}while(exit);

for(int k=0; k<sistema2->totalTiendas(); k++){
        sistema2->obtenerTienda(k).guardarEnArchivo("productos.txt");
}


cout << "Sistema listo.\n";
    return 0;
}
