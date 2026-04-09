#include "graph.h"
#include "graph_traversal.h"
#include <iostream>
#include <fstream>

void parse_input(Graph &g, int &s, int &t, int &L) 
{
    if (!(std::cin >> s >> t >> L))
        throw std::invalid_argument("invalid input format for s t L");

    std::cin.ignore();  

    if (s <= 0 || t <= 0 || L < 0) 
        throw std::invalid_argument(" invalid values for s, t or L\n");

    g.readGraph(std::cin);

    if (s > g.getNumNodes() || t > g.getNumNodes()) 
        throw std::invalid_argument("s or t out of bounds");

}

void solve(Graph &g, int s, int t, int L,
           std::vector<int>& shortestPath, int& minMax,
           std::vector<int>& feasiblePath) {

    g.dijkstra(s - 1, t - 1, shortestPath, minMax);

    g.filterEdges(2 * L);
    g.DFS(s - 1, t - 1, feasiblePath);
}


void output_results(const std::vector<int>& shortestPath, int minMax,
                    const std::vector<int>& feasiblePath,
                    int s, int t, int L) {

    std::cout << "La autonomia mínima de la bateria de un vehículo eléctrico"
              << " para viajar de " << s << " a " << t
              << " es: " << minMax << "\n";
    for (int city : shortestPath)
        std::cout << city + 1 << " ";
    std::cout << "\n";

    if (feasiblePath.empty())
        std::cout << "No existe un camino factible para ir de la ciudad "
                  << s << " a la ciudad " << t
                  << " usando un vehículo eléctrico con autonomía "
                  << 2 * L << "\n";
    else {
         std::cout << "Si existe un camino factible para ir de la ciudad "
                  << s << " a la ciudad " << t
                  << " usando un vehículo eléctrico con autonomía "
                  << 2 * L << ": ";
        for (int city : feasiblePath)
            std::cout << city + 1 << " ";
        std::cout << "\n";
    }
}