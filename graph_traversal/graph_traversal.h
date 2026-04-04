#pragma once
#include "graph.h"

void parse_input(Graph &g, int &s, int &t, int &L);
void solve(Graph &g, int s, int t, int L,
           std::vector<int>& bestPath, int& minMax, bool& isPossible);
void output_results(const std::vector<int>& bestPath, int minMax, bool isPossible, int s, int t, int L);