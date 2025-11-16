#include "sieve.h"
#include <algorithm>

std::vector<int> sieve::primes(int limit) {
    if (limit < 2) {
        return {};
    }
    
    std::vector<bool> sieve(limit + 1, true);
    std::vector<int> primes;
    primes.reserve(limit / (std::log(limit) * 0.8)); // Approximate prime count
    
    sieve[0] = sieve[1] = false;
    
    for (int candidate = 2; candidate * candidate <= limit; candidate++) {
        if (sieve[candidate]) {
            for (int m = candidate * candidate; m <= limit; m += candidate) {
                sieve[m] = false;
            }
        }
    }
    
    for (int i = 2; i <= limit; i++) {
        if (sieve[i]) {
            primes.push_back(i);
        }
    }
    
    return primes;
}