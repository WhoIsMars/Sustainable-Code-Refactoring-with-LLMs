#include "sieve.h"

#include <vector>
#include <bitset>

namespace sieve {

std::vector<int> primes(int limit) {
    if (limit < 2) return {};

    std::vector<bool> marked(limit + 1, false);
    std::vector<int> primes;
    primes.reserve(limit / 2); // Reserve memory to reduce reallocations

    for (int candidate = 2; candidate * candidate <= limit; ++candidate) {
        if (!marked[candidate]) {
            for (int multiple = candidate * candidate; multiple <= limit; multiple += candidate) {
                marked[multiple] = true;
            }
        }
    }

    for (int candidate = 2; candidate <= limit; ++candidate) {
        if (!marked[candidate]) {
            primes.push_back(candidate);
        }
    }

    return primes;
}

}  // namespace sieve