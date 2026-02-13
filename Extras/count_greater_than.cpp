// =================================================================
//
// File: count_larger_than.cpp
// Author: Pablo Javier Arreola Velasco
// Description:
//
//   This program reads a double X and an integer N from standard input,
//   then reads N real values (type double) into an array (one value per line).
//   It counts and outputs how many elements in the array are greater than X.
//
// =================================================================

#include <iostream>

void parse_input(double &x, int &n_elements, double *&arr);
void count_greater_than(const double x, const int n_elements, const double arr[], int &result);
void output_results(const int result);


int main()
{
    double x = 0;
    int n_elements = 0;
    int result = 0;
    double* arr = nullptr;

    parse_input(x,n_elements, arr); 
    count_greater_than(x,n_elements, arr, result); 
    output_results(result); 

    delete[] arr;
    return 0;
}