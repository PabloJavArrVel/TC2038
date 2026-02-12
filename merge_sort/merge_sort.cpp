// =================================================================
//
// File: merge_sort.cpp
// Authors: Pablo Javier Arreola Velasco & Valeria Gisselle Portilla Robles
// Description:
//   Implements the Merge Sort algorithm in C++ using the
//   divide and conquer technique.
//
//   The program reads an integer N from standard input,
//   followed by N real values (double, one per line), and
//   outputs the values sorted in descending order.
//
// =================================================================

#include <vector>
#include <iostream>


// =================================================================
// Merges two already-sorted vectors into one sorted vector (descending order).
// Time complexity analysis:
//
// Let n = tail.size() + head.size().
//
// - We compare elements from both lists sequentially.
// - Each comparison advances either i or j.
// - Each element is processed exactly once.
//
// Therefore, the merge step performs at most n comparisons/push operations.
//
// Time complexity: O(n)
// Space complexity: O(n) for the result vector.
// =================================================================
std::vector<double> sort(const std::vector<double> &tail, const std::vector<double> &head)
{
    std::vector<double> result;

    unsigned int i = 0;
    unsigned int j = 0;

    while (i < tail.size() && j < head.size()) {
        if (tail[i] > head[j]) {
            result.push_back(tail[i]);
            i++;
        } else {
            result.push_back(head[j]);
            j++;
        }
    }
    while (i < tail.size()) {
        result.push_back(tail[i]);
        i++;
    }

    while (j < head.size()) {
        result.push_back(head[j]);
        j++;
    }

    return result;
}


// =================================================================
//    - The vector is repeatedly split into two halves.
//    - Each split reduces problem size by half.
//    - Number of levels of splitting = log₂(n).
//    - And Since we do sort, which time complexity is O(N), log₂(n) times
//    - The fonal time complexity is O(N log₂(n))
// =================================================================
std::vector<double> merge_sort(const std::vector<double> &values, int n)
{
    if(n <= 1)
        return values;
    

    int mid = n / 2; 
    std::vector<double> l(values.begin(), values.begin() + mid); 
    std::vector<double> r(values.begin() + mid, values.begin() + n);

    l=merge_sort(l,mid);
    r=merge_sort(r,mid + (n%2));

    return sort(l,r);
}

int main(int argc, char* argv[])
{
    int N;

    std::cout << "Enter number of values (N): ";
    std::cin >> N;

    std::vector<double> values(N);

    std::cout << "Enter " << N << " values (one per line):\n";
    for (int i = 0; i < N; ++i) {
        std::cin >> values[i];
    }

    std::cout << "\nSorting values...\n";

    std::vector<double> sorted = merge_sort(values, N);

    std::cout << "\n=== Sorted values (descending order) ===\n";
    for (double v : sorted) {
        std::cout << v << std::endl;
    }

    std::cout << "======================================\n";

    return 0;
}