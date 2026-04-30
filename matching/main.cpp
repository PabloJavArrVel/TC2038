/*
Actividad 3.4 Grafos, algoritmos
Descripción:
Programa que modela la asignación de conductores a rutas de entrega de Amazon
como un problema de Maximum Bipartite Matching, resuelto mediante flujo máximo
en una red (algoritmo de Edmonds-Karp / Ford-Fulkerson con BFS).
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
Dado un grafo bipartito G = (C ∪ R, E), donde C son los conductores y R las
rutas, y cada arista (u,v) ∈ E indica que el conductor u puede realizar la
ruta v, se busca encontrar el emparejamiento máximo: el mayor subconjunto de
aristas tal que cada conductor y cada ruta aparezcan a lo sumo una vez.
Se modela como una red de flujo:
  - Fuente S conecta a cada conductor con capacidad 1.
  - Cada conductor conecta a sus rutas disponibles con capacidad 1.
  - Cada ruta conecta al sumidero T con capacidad 1.
El flujo máximo de S a T equivale al matching máximo.
Entrada:
- Una línea con tres enteros c r m (conductores, rutas, relaciones)
- m líneas con dos enteros u v (conductor u puede hacer ruta v)
Salida:
- "Rutas asignadas: X" donde X es el matching máximo
- Lista de pares (conductor ruta) con cada asignación
Referencias:
Cormen, T. H., et al. (2022). Introduction to Algorithms (4th ed.). MIT Press.
GeeksforGeeks. (2026). Maximum Bipartite Matching.
https://www.geeksforgeeks.org/maximum-bipartite-matching/
*/
