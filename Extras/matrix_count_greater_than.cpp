// =================================================================
//
// File: count_larger_than.cpp
// Author: Pablo Javier Arreola Velasco
// Description:
//
//   This program reads from standard input the dimensions of a matrix
//   (rows and columns) and a value X. It then dynamically creates and
//   fills the matrix with integer values entered by the user.
//
//   The program counts how many elements in the matrix are greater
//   than X and outputs the result.
//
// =================================================================

#include <iostream>


void parse_input(int**& matrix, int& rows, int& cols, int& x);
void count_greater_than(const int* const* matrix, const int rows, const int cols, const int x, int& count);
void output_results(const int count);

int main() 
{
    int** matrix = nullptr;
    int rows = 0;
    int cols = 0;
    int x = 0;
    int count = 0;

    parse_input(matrix, rows, cols, x);
    count_greater_than(matrix, rows, cols, x, count);
    output_results(count);

    for (int i = 0; i < rows; i++)
        delete[] matrix[i];
    delete[] matrix;

    return 0;
}
