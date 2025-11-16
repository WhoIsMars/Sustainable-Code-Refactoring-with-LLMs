#include "nth_prime.h"
#include <stdexcept>

unsigned long nth_prime::nth(const unsigned long &num) {
    if (num == 0) { throw std::domain_error("No zeroth prime"); }
    if (num == 1) { return 2; }
    unsigned long primes_found {1}, last_prime {2}, candidate {3};
    while (primes_found < num) {
        if (is_prime(candidate)) {
            last_prime = candidate;
            ++primes_found;
        }
        (++candidate)++;
    }
    return last_prime;
}

bool nth_prime::is_prime(const int &num) noexcept {
    if (num <= 3) return num > 1;
    if (num % 2 == 0 || num % 3 == 0) return false;
    for (int i = 5; i * i <= num; i += 6)
        if (num % i == 0 || num % (i + 2) == 0) 
                return false;
    return true;
}
