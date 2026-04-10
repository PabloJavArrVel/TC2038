#include "Graph.h"
#include "coloring.h"
#include <iostream>

void solve(Graph& g, std::vector<int>& schedule, bool& feasibility)
{
    g.BFSColoring(0,schedule);

    if(!schedule.empty())
        feasibility = true;

}

void output_results(const std::vector<int>& schedule, bool feasibility)
{
    if(feasibility){
         std::cout << "true"<<std::endl;
         for (int i = 0; i < schedule.size(); i++) {
            std::cout << (i + 1) << " " << schedule[i] << std::endl;
        }
    }
    else{
        std::cout << "false"<<std::endl;
    }

}