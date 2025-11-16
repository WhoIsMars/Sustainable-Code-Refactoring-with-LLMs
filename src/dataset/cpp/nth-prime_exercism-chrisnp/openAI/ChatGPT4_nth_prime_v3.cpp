#include "nth_prime.h"
#include <stdexcept>
#include <vector>

unsigned long nth_prime::nth(const unsigned long &num) {
    if (num == 0) { throw std::domain_error("No zeroth prime"); }
    if (num == 1) { return 2; }

    std::vector<bool> sieve;
    unsigned long limit = num * (std::log(num) + std::log(std::log(num))); // Approximation for nth prime
    sieve.resize(limit + 1, true);
    sieve[0] = sieve[1] = false;

    for (unsigned long i = 2; i * i <= limit; ++i) {
        if (sieve[i]) {
            for (unsigned long j = i * i; j <= limit; j += i) {
                sieve[j] = false;
            }
        }
    }

    unsigned long primes_found = 0;
    for (unsigned long i = 2; i <= limit; ++i) {
        if (sieve[i]) {
            ++primes_found;
            if (primes_found == num) {
                return i;
            }
        }
    }

    throw std::runtime_error("Prime calculation failed");
}

bool nth_prime::is_prime(const int &num) noexcept {
    if (num <= 3) return num > 1;
    if (num % 2 == 0 || num % 3 == 0) return false;
    for (int i = 5; i * i <= num; i += 6)
        if (num % i == 0 || num % (i + 2) == 0) 
            return false;
    return true;
}