Este documento describe la implementación de un sistema de gestión de cadena
de suministro desarrollado en lenguaje C++. El sistema fue construido con un
enfoque modular, utilizando estructuras de datos fundamentales y avanzadas
para cubrir todos los aspectos del proceso logístico, desde la gestión de inventario
hasta la distribución de productos y atención a clientes.
La solución fue desarrollada mediante una arquitectura estructurada basada en
archivos header, donde cada uno representa un componente o módulo del
sistema. Estas estructuras fueron integradas a través de un archivo principal, el
cual contiene el menú interactivo y la lógica de ejecución.
El sistema resuelve operaciones típicas como el registro de productos,
procesamiento de pedidos, control de transacciones, búsqueda eficiente,
ordenamiento, balanceo automático de estructuras, y manejo de rutas mediante
grafos. Todo esto con mecanismos de persistencia y recuperación de datos
mediante archivos planos.
Arbol_binario.h
Contiene la implementación del Árbol Binario de Búsqueda para categorización
de productos. Búsqueda eficiente por tipo o categoría. Inserciones ordenadas con
base en criterios definidos (por ejemplo, código o nombre del producto).
Avl.h
Implementa un árbol AVL para mantener un inventario balanceado. Mantiene el
equilibrio automático tras inserciones/eliminaciones. Usado para indexación del
inventario, asegurando tiempos de búsqueda óptimos en todo momento. Mejora
el rendimiento frente a árboles binarios no balanceados.
Cola.h
Define la estructura de cola para gestionar pedidos en orden FIFO. Utilizada
para la gestión de pedidos de clientes. Procesa los pedidos en el orden en que
se reciben. Incluye funciones de enqueue, dequeue, y verificación de estado de
la cola.
Grafo.h
Contiene la estructura de un grafo dirigido/no dirigido. Modela la red de
distribución de productos entre almacenes, rutas de entrega y clientes. Permite
aplicar algoritmos como BFS y DFS para encontrar rutas y optimizar entregas.
Inventario.h
Define funciones relacionadas con la gestión del inventario. Permitiendo realizar
las siguientes operaciones:
• Registro de productos.
• Actualización de cantidades.
• Eliminación de productos.
Además de que cuenta con Interfaces para conectarse con otras estructuras
como AVL o lista doble.
Lista_doble.h
La lista doble es usada para gestionar los productos dentro del sistema con
capacidad de recorrer en ambos sentidos. Permite eliminar o insertar productos
fácilmente desde cualquier punto de la lista.
Lista_simple.h
La lista simple es usada para mantener un historial de transacciones o logs de
operaciones realizadas. Registro en orden cronológico de movimientos como
ventas, ingresos y salidas.
Main.cpp
Archivo principal que contiene el menú y las llamadas a las funciones de los
headers.
Operacion.h
Contiene las operaciones generales del sistema. Como alta y baja de productos,
procesamiento de pedidos, etc. Se integra con la pila para funciones de undo/redo.
Pedido.h
Define la estructura y funciones para manejar pedidos. Incluye los campos
necesarios como ID, productos solicitados, cantidad, y cliente. Se integra con la
cola para el flujo de atención.
Pila.h
Implementa una pila LIFO usada en funcionalidades. Se usa para gestionar
operaciones de usuario con funciones de deshacer (undo) y rehacer (redo).
También se emplea para validaciones y control interno de acciones.
Producto.h
Contiene la definición del producto y funciones para manipularlo. Además de darle
atributos al producto como: ID, nombre, cantidad, categoría, precio, etc.
Es el objeto principal que interactúa con inventario, árboles y listas.
Serializador.h
Se encarga de guarda el estado del sistema en archivos .txt. Restaura los datos
al iniciar el sistema, asegurando persistencia. Permite exportar e importar
productos, pedidos y transacciones.
Sistemalnv.h
Contiene la lógica general del sistema de inventario.
Es un archivo auxiliar que contiene funciones generales del sistema de inventario,
como:
• Inicialización de estructuras.
• Operaciones integradas (alta, baja, búsqueda, edición).
• Funciones de interfaz que conectan con el menú principal
