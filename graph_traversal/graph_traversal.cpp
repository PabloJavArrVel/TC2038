#include "graph.h"
#include "graph_traversal.h"
#include <iostream>
#include <fstream>

void parse_input(Graph &g, int &s, int &t, int &L) 
{
    if (!(std::cin >> s >> t >> L))
        throw std::invalid_argument("invalid input format for s t L");

    std::cin.ignore();  // consume the leftover newline

    if (s <= 0 || t <= 0 || L < 0) 
        throw std::invalid_argument(" invalid values for s, t or L\n");

    g.readGraph(std::cin);

    if (s > g.getNumNodes() || t > g.getNumNodes()) 
        throw std::invalid_argument("s or t out of bounds");

}

void solve(Graph &g, int s, int t, int L,
           std::vector<int>& bestPath, int& minMax, bool& isPossible) {
    int bestMax = INT_MAX;
    std::vector<bool> visited(g.getNumNodes(), false);
    std::vector<int> path;

    g.dfsMinimax(s - 1, t - 1, visited, path, 0, bestMax, bestPath);

    if (!bestPath.empty()) {
        minMax = bestMax;
        if (bestMax <= L)
            isPossible = true;
    }
}

void output_results(const std::vector<int>& bestPath, int minMax, bool isPossible, int s, int t, int L)
{
    std::ofstream out("output.txt");
    out << "La autonomia minima de la bateria de un vehiculo electrico para viajar de "
        << s << " a " << t << " es: " << minMax << std::endl;
    if (!isPossible) {
        out << "No existe un camino factible para ir de la ciudad " << s 
            << " a la ciudad " << t 
            << " usando un vehiculo con autonomia " << L << std::endl;
    } else {
       for (auto& city : bestPath) {
            out << city + 1 << " ";
        }
        out << std::endl;
    }
}