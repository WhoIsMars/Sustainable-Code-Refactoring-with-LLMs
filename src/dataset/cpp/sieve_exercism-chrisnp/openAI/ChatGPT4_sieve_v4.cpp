#include "sieve.h"
#include <vector>

std::vector<int> sieve::primes(int limit) {
    if (limit < 2) return {};

    std::vector<bool> sieve(limit + 1, true);
    sieve[0] = sieve[1] = false;
    std::vector<int> primes;
    primes.reserve(limit / 2); // Reserve approximate space to reduce reallocations

    for (int candidate = 2; candidate * candidate <= limit; ++candidate) {
        if (sieve[candidate]) {
            for (int m = candidate * candidate; m <= limit; m += candidate) {
                sieve[m] = false;
            }
        }
    }

    for (int candidate = 2; candidate <= limit; ++candidate) {
        if (sieve[candidate]) {
            primes.push_back(candidate);
        }
    }

    return primes;
}