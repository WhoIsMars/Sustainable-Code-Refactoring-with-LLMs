#include "sieve.h"
#include <algorithm>

std::vector<int> sieve::primes(int limit) {

    std::vector<bool> sieve(limit + 1, true);
    std::vector<int> primes {};
    for (int candidate = 2; candidate <= limit; candidate++) {
        if (!sieve[candidate]) {
            continue;
        }
        primes.insert(primes.end(), candidate);
        for (int m = candidate; m <= limit; m += candidate) {
            sieve[m] = false;
        }
    }   
    return primes;
}
