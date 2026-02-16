// Declares input parsing utilities and functions for counting
// elements greater than a specified value in arrays and matrices.
#pragma once
#include <vector>

void parse_array(int &x, std::vector<int> &arr);
void parse_matrix(int &x, std::vector<std::vector<int> > &matrix);

int count_greater_than(const std::vector<int> &arr,size_t begin, size_t end, int x);
int count_greater_than(const std::vector<std::vector<int> > &matrix,  size_t row, int x);

