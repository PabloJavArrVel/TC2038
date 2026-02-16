// =================================================================
//
// File: count_greater_than.cpp
// Author: Pablo Javier Arreola Velasco
//
// Description:
//   Provides utility functions to:
//
//   - Read an integer value and a collection of integers
//     (either a 1D array or 2D matrix) from standard input.
//
//   - Count how many elements in the collection are greater
//     than a specified value.
//
//   The counting logic uses recursive divide-and-conquer for
//   arrays and recursive row traversal for matrices.
//
// =================================================================

#include "count_greater_than.h"  
#include <vector>
#include <iostream>


// Reads a comparison value and a list of integers from standard input.
//
// Parameters:
//   x   - (output) value to compare elements against
//   arr - (output) vector that will store the input elements
//
// Behavior:
//   Prompts the user for:
//     - comparison value
//     - number of elements
//     - each element of the array
//
//   The vector is resized based on user input.
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

// Reads a comparison value and a 2D matrix of integers from standard input.
//
// Parameters:
//   x      - (output) value to compare elements against
//   matrix - (output) 2D vector storing matrix elements
//
// Behavior:
//   Prompts the user for:
//     - comparison value
//     - number of rows and columns
//     - matrix elements
//
//   The matrix is resized according to the specified dimensions.
void parse_matrix(int &x, std::vector<std::vector<int> > &matrix)
{
    int rows, cols;

    std::cout << "Enter the value to compare (x): ";
    std::cin >> x;

    std::cout << "Enter number of rows: ";
    std::cin >> rows;

    std::cout << "Enter number of columns: ";
    std::cin >> cols;

    matrix.resize(rows, std::vector<int>(cols));

    std::cout << "Enter the matrix elements:\n";

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            std::cin >> matrix[i][j];
        }
    }
}

// Counts elements greater than a given value within a range of an array.
//
// Parameters:
//   arr   - input array
//   begin - starting index (inclusive)
//   end   - ending index (exclusive)
//   x     - comparison value
//
// Returns:
//   Number of elements in arr[begin, end) that are greater than x.
//
// Notes:
//   Uses recursive divide-and-conquer.
int count_greater_than(const std::vector<int> &arr, size_t begin,
    size_t end, int x)
{
     if (begin == end)
        return 0;
    else if (end == begin + 1)
        return ((arr[begin] > x)? 1 : 0);

    size_t mid = (begin + (end - begin)/2);

    return count_greater_than(arr, begin, mid, x) + count_greater_than(arr, mid, end, x);
}


// Counts elements greater than a given value in a 2D matrix.
//
// Parameters:
//   matrix - input matrix
//   row    - current row index (used for recursive traversal)
//   x      - comparison value
//
// Returns:
//   Total number of elements in the matrix greater than x.
//
// Notes:
//   Processes one row at a time recursively.
int count_greater_than(const std::vector<std::vector<int> > &matrix, 
    size_t row, int x)
{
    if (row==matrix.size())
        return 0;
    
    int this_row_count = count_greater_than(matrix[row],0,matrix[row].size(),x);
    int next_row_count = count_greater_than(matrix,row + 1, x);    

    return this_row_count + next_row_count;

}


