// =================================================================
//
// File: count_greater_than.cpp
// Author: Pablo Javier Arreola Velasco
// Description:
//
//   This program reads a double X and an integer N from standard input,
//   then reads N real values (type double) into an array (one value per line).
//   It counts and outputs how many elements in the array are greater than X.
//
// =================================================================


#include "count_greater_than.h"  
#include <vector>
#include <iostream>



void parse_array(int &x, std::vector<int> &arr)
{
    int n;

    std::cout << "Enter the value to compare (x): ";
    std::cin >> x;

    std::cout << "How many elements in the array? ";
    std::cin >> n;

    arr.resize(n);

    std::cout << "Enter " << n << " elements:\n";
    for (int i = 0; i < n; ++i) {
        std::cin >> arr[i];
    }
}


// void parse_matrix(int &x, std::vector<std::vector<int>> &matrix)
// {
//     int rows, cols;

//     std::cout << "Enter the value to compare (x): ";
//     std::cin >> x;

//     std::cout << "Enter number of rows: ";
//     std::cin >> rows;

//     std::cout << "Enter number of columns: ";
//     std::cin >> cols;

//     matrix.resize(rows, std::vector<int>(cols));

//     std::cout << "Enter the matrix elements:\n";

//     for (int i = 0; i < rows; ++i) {
//         for (int j = 0; j < cols; ++j) {
//             std::cin >> matrix[i][j];
//         }
//     }
// }


int count_greater_than(const std::vector<int> &arr,size_t begin,
    size_t end, int x)
{
     if (begin == end)
        return 0;
    else if (end == begin + 1)
        return ((arr[begin] > x)? 1 : 0);

    size_t mid = (begin + (end - begin)/2);

    return count_greater_than(arr, begin, mid, x) + count_greater_than(arr, mid, end, x);
}

// int count_greater_than(const std::vector<std::vector<int>> &matrix, int x)
// {


// }
