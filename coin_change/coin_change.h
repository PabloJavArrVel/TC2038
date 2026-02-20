#pragma once
#include <vector>

std::vector<int> parseInput(int &P, int &Q);
std::vector<int> greedyCoinChange(const std::vector<int> &denominations,
     const int P, const int Q);
void outputResult(const std::vector<int> &denominations,
                  const std::vector<int> &change);