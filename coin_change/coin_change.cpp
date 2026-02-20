#include "coin_change.h"
#include <vector>
#include <stdexcept>
#include <iostream>




// Using a greedy approach, computes the change to be returned
// to a customer using the available currency denominations.
//
// Parameters:
// - denominations (const std::vector<int>&): A vector of integers representing
//   the available currency denominations.
// - P (const int): The price of the product.
// - Q (const int): The amount paid by the customer.
//
// Returns:
// - std::vector<int>: A vector of integers representing the denominations
//   required to provide the change (Q − P), expressed in terms of the
//   available denominations.

std::vector<int> greedyCoinChange(const std::vector<int> &denominations, 
    const int P, const int Q) {

    if (Q < P)
        throw std::invalid_argument("amount paid is less than price");

    std::vector<int> change;
    int remainder = Q - P;

    for (int coin : denominations) {
        while (coin <= remainder) {
            remainder -= coin;
            change.push_back(coin);
        }
    }

    if(remainder != 0)
        throw std::invalid_argument("exact change not possible");

    return change;

}

// Parses the input required for the coin change program
// from standard input.
//
// Parameters:
// - P (int&): Reference where the price of the product will be stored.
// - Q (int&): Reference where the amount paid by the customer will be stored.
//
// Input format:
// - An integer N representing the number of available denominations.
// - N integers (one per line) representing the coin denominations.
// - An integer P representing the product price.
// - An integer Q representing the amount paid.
//
// Returns:
// - std::vector<int>: A vector containing the valid currency denominations.
//
// Throws:
// - std::invalid_argument if:
//     * N is less than or equal to 0
//     * Any denomination is less than or equal to 0
std::vector<int> parseInput(int &P, int &Q)
{
    int N;
    std::cin >> N;

    if (N <= 0)
        throw std::invalid_argument("invalid number of denominations");

    std::vector<int> denominations(N);

    for (int i = 0; i < N; ++i)
    {
        std::cin >> denominations[i];

        if (denominations[i] <= 0)
            throw std::invalid_argument("denominations must be positive");
    }

    std::cin >> P;
    std::cin >> Q;

    return denominations;
}

// Outputs the result in the required format:
//
// Following lines: how many times each denomination was used,
// in the original input order.
//
// Parameters:
// - denominations (const std::vector<int>&): Original denominations.
// - change (const std::vector<int>&): Coins returned by greedy algorithm.
void outputResult(const std::vector<int> &denominations,
                  const std::vector<int> &change)
{
    std::vector<int> counts(denominations.size(), 0);

    for (int coinUsed : change)
    {
        for (int i = 0; i < denominations.size(); ++i)
        {
            if (denominations[i] == coinUsed)
            {
                counts[i]++;
                break;
            }
        }
    }

    for (int c : counts)
        std::cout << c << std::endl;
}