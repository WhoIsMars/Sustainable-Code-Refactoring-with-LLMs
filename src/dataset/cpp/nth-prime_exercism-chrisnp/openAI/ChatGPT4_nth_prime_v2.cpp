#include "nth_prime.h"
#include <stdexcept>
#include <vector>
#include <cmath>

unsigned long nth_prime::nth(const unsigned long &num) {
    if (num == 0) { throw std::domain_error("No zeroth prime"); }
    if (num == 1) { return 2; }

    std::vector<unsigned long> primes = {2};
    unsigned long candidate = 3;

    while (primes.size() < num) {
        bool is_prime = true;
        unsigned long limit = std::sqrt(candidate);
        for (const auto &prime : primes) {
            if (prime > limit) break;
            if (candidate % prime == 0) {
                is_prime = false;
                break;
            }
        }
        if (is_prime) {
            primes.push_back(candidate);
        }
        candidate += 2; // Skip even numbers
    }
    return primes.back();
}

bool nth_prime::is_prime(const int &num) noexcept {
    if (num <= 3) return num > 1;
    if (num % 2 == 0 || num % 3 == 0) return false;
    for (int i = 5; i * i <= num; i += 6)
        if (num % i == 0 || num % (i + 2) == 0) 
            return false;
    return true;
}