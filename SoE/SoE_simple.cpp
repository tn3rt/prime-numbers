#include <iostream>
#include <vector>
#include "SoE_simple.h"

void sift(std::vector<bool>::iterator, int);

const int limit = 10000000;

int main()
{
    std::vector<int> sieve(limit);
    sift(begin(sieve), limit);

    for (int i=0; i < limit; ++i) 
        if (sieve[i])
            std::cout << (2*i+3) << std::endl;

    return 0;
}
