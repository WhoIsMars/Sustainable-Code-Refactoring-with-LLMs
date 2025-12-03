#include "nth_prime.h"
#include <cmath>
#include <stdexcept>

namespace prime {

    int nth(unsigned long n) {
        if (n < 1) {
            throw std::domain_error("Non positive number given!");
        }

        if (n == 1) return 2;

        // Estimate the nth prime using the prime number theorem.  This avoids unnecessary iterations.
        unsigned long upper_bound = static_cast<unsigned long>(n * (log(n) + log(log(n))));
        if (upper_bound < 100) upper_bound = 100; // handle small n

        std::vector<bool> is_prime(upper_bound + 1, true);
        is_prime[0] = is_prime[1] = false;

        // Sieve of Eratosthenes
        for (unsigned long p = 2; p * p <= upper_bound; ++p) {
            if (is_prime[p]) {
                for (unsigned long i = p * p; i <= upper_bound; i += p) {
                    is_prime[i] = false;
                }
            }
        }

        std::vector<int> primes;
        for (unsigned long p = 2; p <= upper_bound; ++p) {
            if (is_prime[p]) {
                primes.push_back(static_cast<int>(p));
                if (primes.size() == n) {
                    return primes.back();
                }
            }
        }

        // Should not happen, but handle potential errors.
        throw std::runtime_error("Prime number not found within estimated range.");
    }

}