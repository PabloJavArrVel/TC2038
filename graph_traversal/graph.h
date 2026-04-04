#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <set>
#include <stack>
#include <queue>


class Graph {
  private:
    int numNodes;
    int numEdges;
    // Lista de adyacencia
    // vector de listas ligadas de pares (vertice, peso)
    std::vector<std::list<std::pair<int, int>>> adjList;
  
    void split(std::string line, std::vector<int> &res);
  
  public:
    int getNumNodes() const;
    Graph();
    ~Graph();
    void readGraph(std::istream &input);
    void print();
    void DFS(int v, int t);
    void dfsMinimax(int v, int t,
                std::vector<bool>& visited,
                std::vector<int>& path,
                int currentMax,
                int& bestMax,
                std::vector<int>& bestPath);
    void BFS(int v);
};
