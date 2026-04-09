#pragma once
#include "graph.h"

void parse_input(Graph &g, int &s, int &t, int &L);
void solve(Graph &g, int s, int t, int L,
           std::vector<int>& shortestPath, int& minMax,
           std::vector<int>& feasiblePath);
void output_results(const std::vector<int>& shortestPath, int minMax,
                    const std::vector<int>& feasiblePath,
                    int s, int t, int L);