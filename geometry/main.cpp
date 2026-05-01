/*
Actividad 4.1 Geometría Computacional
Descripción:
Programa que encuentra los dos talleres de producción de fuegos artificiales
artesanales más cercanos entre sí en Tultepec, Estado de México, utilizando
el algoritmo 
Equipo 4:
Gisselle Portilla - A01752371
Pablo Javier Arreola - A01747824
Fecha:
2026-04-30
Compilar:
g++ -std=c++17 -O3 main.cpp -o main
Ejecución:
./main < in.txt
Descripción del problema:
Dados N talleres con nombre y coordenadas (X, Y), encontrar el par de talleres
con menor distancia euclidiana entre sí. Se utiliza un algoritmo de divide y
vencerás que ordena los puntos por coordenada X, divide el conjunto en dos
mitades, resuelve recursivamente cada mitad y combina los resultados revisando
la franja central de ancho 2δ, donde δ es el mínimo de las dos distancias
encontradas. Esto garantiza complejidad O(n log n).
Entrada:
- Un entero N indicando la cantidad de talleres (2 <= N <= 10^6)
- N líneas con formato: Nombre X Y
Salida:
- "Los dos talleres que más riesgo representan en Tultepec son A y B (distancia D)"
  donde D es la distancia euclidiana con dos decimales
Referencias:
Cormen, T. H., et al. (2022). Introduction to Algorithms (4th ed.). MIT Press.
Shamos, M. I., & Hoey, D. (1975). Closest-point problems. 16th Annual Symposium
on Foundations of Computer Science. IEEE.
*/

#include <iostream>
#include "Point.h"
#include "Workshop.h"
#include "Algorithm.h"



int main(){
    try {
        std::ios::sync_with_stdio(false);
        std::cin.tie(nullptr);

        std::vector<Workshop> workshops = parse_input();
        auto result = solve(workshops);
        output_results(result);
    }
    catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
}