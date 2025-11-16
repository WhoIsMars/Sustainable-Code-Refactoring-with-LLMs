#include "nth_prime.h"

#include <stdexcept>
#include <vector>
#include <cmath>

namespace nth_prime {

bool is_prime(int i) {
    if (i < 2) return false;
    if (i == 2) return true;
    if (i % 2 == 0) return false;
    
    int limit = static_cast<int>(std::sqrt(i));
    for (int j = 3; j <= limit; j += 2) {
        if (i % j == 0) return false;
    }
    return true;
}

int nth(int i) {
    if (i <= 0) throw std::domain_error("invalid i");
    
    if (i == 1) return 2;
    
    std::vector<int> primes;
    primes.reserve(i);
    primes.push_back(2);
    
    int candidate = 3;
    while (static_cast<int>(primes.size()) < i) {
        bool is_prime_candidate = true;
        int limit = static_cast<int>(std::sqrt(candidate));
        
        for (int prime : primes) {
            if (prime > limit) break;
            if (candidate % prime == 0) {
                is_prime_candidate = false;
                break;
            }
        }
        
        if (is_prime_candidate) {
            primes.push_back(candidate);
        }
        candidate += 2;
    }
    
    return primes[i - 1];
}

}  // namespace nth_prime