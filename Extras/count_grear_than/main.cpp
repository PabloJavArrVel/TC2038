#include <iostream>
#include <string>
#include <vector>
#include "count_greater_than.h"   

static void run_array_mode();
// static void run_matrix_mode();

int main(int argc, char* argv[]) 
{
    if (argc < 2) {
        std::cout << "Usage: ./program [array | matrix]\n";
        return 1;
    }

    std::string mode = argv[1];

    if (mode == "array") {
        run_array_mode();
    }
    // else if (mode == "matrix") {
    //     run_matrix_mode();
    // }
    else {
        std::cout << "Invalid mode. Use 'array' or 'matrix'.\n";
        return 1;
    }

    return 0;
}

static void run_array_mode() 
{
    int x;
    std::vector<int> arr;

    parse_array(x, arr);

    int result = count_greater_than(arr, 0, arr.size(), x);

    std::cout<<"The result is... "<<result<<"\n";
}

// static void run_matrix_mode() 
// {
//     int x;
//     std::vector<std::vector<int>> matrix;

//     parse_matrix(x, matrix);

//     int result = count_greater_than(matrix, x);

//     std::cout<<"The result is... "<<result<<"\n";
// }
