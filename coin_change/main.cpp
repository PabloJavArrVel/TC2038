#include "coin_change.h"
#include <iostream>
#include <vector>

int main()
{
    try
    {
        int P = 0;
        int Q = 0;

        std::vector<int> denominations = parseInput(P, Q);

        std::vector<int> change =
            greedyCoinChange(denominations, P, Q);

        outputResult(denominations, change);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}