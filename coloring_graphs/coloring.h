#include "Graph.h"
#include <vector>

// Checks if the graph is bipartite and generates the assignment
void solve(Graph& g, std::vector<int>& schedule, bool& feasibility);

// Outputs the result based on bipartition status
void output_results(const std::vector<int>& schedule, bool feasibility);

