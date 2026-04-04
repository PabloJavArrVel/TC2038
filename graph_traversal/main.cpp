/*
Actividad 3.2 Grafos y sus recorridos

Descripción:
Programa que modela un conjunto de ciudades como un grafo dirigido ponderado
para resolver problemas relacionados con rutas para vehículos eléctricos.
El programa calcula la autonomía mínima necesaria para viajar entre dos ciudades
y determina si existe una ruta factible bajo una restricción de distancia máxima
por carretera.

Equipo 4:
Gisselle Portilla - A01752371
Pablo Javier Arreola - A01747824

Fecha:
2026-07-04

Compilar:
g++ -std=c++17 -O3 main.cpp -o main

Ejecución con redirección:
./main < test01.txt > out01.txt
./main < test02.txt > out02.txt
./main < test03.txt > out03.txt
./main < test04.txt > out04.txt
./main < test05.txt > out05.txt

Ejecución automática de pruebas:
make -> make test

Limpiar archivos generados:
make clean


Descripción del problema:
Dado un grafo dirigido ponderado G = (V, E), donde los vértices representan ciudades
y las aristas representan carreteras con una longitud asociada, se resuelven:

1. Determinar la autonomía mínima de batería necesaria para viajar de una ciudad
   origen s a una ciudad destino t.
2. Determinar si existe una ruta factible de s a t tal que todas las aristas
   tengan longitud menor o igual a L, y en caso afirmativo, mostrar el camino.

Entrada:
- Una línea con tres enteros: s t L
- Una línea con dos enteros: N M
- M líneas con tres enteros: u v w

Salida:
1. La autonomía mínima requerida o un mensaje indicando que no existe camino.
2. El camino factible (si existe) o un mensaje indicando que no es posible
   bajo la restricción L.

Referencias:
Cormen, T. H., et al. (2009). Introduction to Algorithms (3rd ed.). MIT Press.
Dijkstra, E. W. (1959). A note on two problems in connexion with graphs.
GeeksforGeeks. (2025). Dijkstra’s shortest path algorithm.
https://www.geeksforgeeks.org/dijkstras-shortest-path-algorithm-greedy-algo-7/
GeeksforGeeks. (2025). BFS for graph traversal.
https://www.geeksforgeeks.org/breadth-first-search-or-bfs-for-a-graph/
*/


#include <iostream>
#include "graph_traversal.h"

int main() {
   try {
      std::ios::sync_with_stdio(false);
      std::cin.tie(nullptr);

      Graph g;
      int s, t, L;
      int minMax = -1;
      bool isPossible = false;
      std::vector<int> bestPath;

      parse_input(g, s, t, L);
      solve(g, s, t, L, bestPath, minMax, isPossible);
      output_results(bestPath, minMax, isPossible,s,t,L);
   } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}