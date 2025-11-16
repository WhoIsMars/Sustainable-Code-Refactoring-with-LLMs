#include "nth_prime.h"
#include <stdexcept>
#include <vector>

unsigned long nth_prime::nth(const unsigned long &num) {
    if (num == 0) { throw std::domain_error("No zeroth prime"); }
    if (num == 1) { return 2; }
    if (num == 2) { return 3; }
    
    std::vector<unsigned long> primes;
    primes.reserve(num > 1000 ? 1000 : num);
    primes.push_back(2);
    primes.push_back(3);
    
    unsigned long candidate = 5;
    while (primes.size() < num) {
        if (is_prime_optimized(candidate, primes)) {
            primes.push_back(candidate);
        }
        candidate += 2;
    }
    return primes.back();
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

bool nth_prime::is_prime_optimized(unsigned long num, const std::vector<unsigned long>& known_primes) noexcept {
    if (num <= 3) return num > 1;
    if (num % 2 == 0 || num % 3 == 0) return false;
    
    for (const auto& prime : known_primes) {
        if (prime * prime > num) break;
        if (prime > 3 && num % prime == 0) return false;
    }
    return true;
}