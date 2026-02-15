#pragma once
#include <vector>

void parse_array(int &x, std::vector<int> &arr);
void parse_matrix(std::vector<std::vector<int>> &matrix, int &x);

int count_greater_than(const std::vector<int> &arr, int x);
int count_greater_than(const std::vector<std::vector<int>> &matrix, int x);

void output_results(int result);
