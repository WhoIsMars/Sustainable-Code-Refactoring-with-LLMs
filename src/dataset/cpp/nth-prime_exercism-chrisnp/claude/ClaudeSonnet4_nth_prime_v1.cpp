#include "nth_prime.h"
#include <stdexcept>
#include <vector>

unsigned long nth_prime::nth(const unsigned long &num) {
    if (num == 0) { throw std::domain_error("No zeroth prime"); }
    if (num == 1) { return 2; }
    if (num == 2) { return 3; }
    
    static std::vector<unsigned long> prime_cache = {2, 3};
    
    if (num <= prime_cache.size()) {
        return prime_cache[num - 1];
    }
    
    unsigned long candidate = prime_cache.back() + 2;
    
    while (prime_cache.size() < num) {
        if (is_prime(candidate)) {
            prime_cache.push_back(candidate);
        }
        candidate += 2;
    }
    
    return prime_cache[num - 1];
}

bool nth_prime::is_prime(const int &num) noexcept {
    if (num <= 3) return num > 1;
    if (num % 2 == 0 || num % 3 == 0) return false;
    for (int i = 5; i * i <= num; i += 6) {
        if (num % i == 0 || num % (i + 2) == 0) 
            return false;
    }
    return true;
}