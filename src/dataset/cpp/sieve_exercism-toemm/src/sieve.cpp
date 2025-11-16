#include "sieve.h"

#include <vector>
#include <bitset>

namespace sieve {



std::vector<int> primes(int limit) {


    std::vector<bool> marked(limit + 1, false);
    std::vector<int> primes{};


    for (int candidate = 2; candidate <= limit; candidate++) {
        if (marked[candidate]) continue;

        marked[candidate] = true;
        
        primes.push_back(candidate);

        for (int multiple = candidate * candidate; multiple <= limit; multiple += candidate) 
            marked[multiple] = true;

    }

    return primes;

}



}  // namespace sieve
