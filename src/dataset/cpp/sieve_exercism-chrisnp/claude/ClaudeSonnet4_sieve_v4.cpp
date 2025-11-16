#include "sieve.h"
#include <algorithm>

std::vector<int> sieve::primes(int limit) {
    if (limit < 2) {
        return {};
    }
    
    std::vector<bool> is_prime(limit + 1, true);
    std::vector<int> primes;
    primes.reserve(limit / (std::log(limit) * 0.8));
    
    is_prime[0] = is_prime[1] = false;
    
    for (int candidate = 2; candidate * candidate <= limit; ++candidate) {
        if (is_prime[candidate]) {
            for (int multiple = candidate * candidate; multiple <= limit; multiple += candidate) {
                is_prime[multiple] = false;
            }
        }
    }
    
    for (int i = 2; i <= limit; ++i) {
        if (is_prime[i]) {
            primes.push_back(i);
        }
    }
    
    return primes;
}