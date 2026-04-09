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
    std::vector<std::list<std::pair<int, int>>> adjList;
  
    void split(std::string line, std::vector<int> &res);
  
  public:
    int getNumNodes() const;
    Graph();
    ~Graph();
    void readGraph(std::istream &input);
    void filterEdges(int maxWeight);
    void print();
    void DFS(int s, int t, std::vector<int>& path);
    void dijkstra(int s, int t, std::vector<int>& path, int& maxEdge);
    void BFS(int v);
};