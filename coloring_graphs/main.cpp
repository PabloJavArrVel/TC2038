/*
Actividad 3.3 Grafos, algoritmos

Descripción:
Programa que modela las incompatibilidades entre trabajadores de un hospital
como un grafo no dirigido, con el fin de determinar si es posible asignarlos
a dos turnos sin que empleados incompatibles coincidan en el mismo turno.
Este problema se modela como la verificación de si el grafo es bipartito.

Equipo 4:
Gisselle Portilla - A01752371
Pablo Javier Arreola - A01747824

Fecha:
2026-10-04

Compilar:
g++ -std=c++17 -O3 main.cpp -o main

Ejecución:
./main < in.txt > out.txt

Descripción del problema:
Dado un grafo no dirigido G = (V, E), donde los vértices representan empleados
y las aristas representan incompatibilidades, se debe determinar si es posible
dividir los vértices en dos conjuntos disjuntos (turnos) tales que no exista
ninguna arista entre vértices del mismo conjunto. Esto equivale a verificar si
el grafo es bipartito.

Entrada:
- Una línea con dos enteros N M (número de empleados y número de incompatibilidades)
- M líneas con dos enteros u v (incompatibilidad entre empleados u y v)

Salida:
- "True" seguido de una asignación válida (persona turno)
- "False" si no es posible realizar la asignación


Referencias:
GeeksforGeeks. (2026). Bipartite Graphs.
https://www.geeksforgeeks.org/dsa/what-is-bipartite-graph/
Weisstein, Eric W. "Bipartite Graph." From MathWorld--A Wolfram Resource. https://mathworld.wolfram.com/BipartiteGraph.html

*/

#include "Graph.h"
#include "coloring.h"
#include <iostream>
#include <vector>


int main() 
{
   try {
      std::ios::sync_with_stdio(false);
      std::cin.tie(nullptr);

      Graph g;
      std::vector<int> schedule; // schedule[v]->1|2 where v is an employee and 1/2 is his shift
      bool isFeasible = false;

      g.readGraph(std::cin);

      solve(g, schedule, isFeasible);
      output_results(schedule, isFeasible);
   } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}