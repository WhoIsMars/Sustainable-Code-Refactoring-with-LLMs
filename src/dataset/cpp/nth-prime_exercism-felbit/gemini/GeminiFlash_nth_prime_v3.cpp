#include "nth_prime.h"
#include <cmath>
#include <stdexcept>
#include <vector>

namespace prime {

    int nth(unsigned long n) {
        if (n < 1) {
            throw std::domain_error("Non positive number given!");
        }

        if (n <= 6) {
            int small_primes[] = {2, 3, 5, 7, 11, 13};
            return small_primes[n - 1];
        }

        std::vector<int> primes;
        primes.reserve(n);
        primes.push_back(2);

        int candidate = 3;
        while (primes.size() < n) {
            bool is_prime = true;
            int sqrt_candidate = std::sqrt(candidate);
            for (int p : primes) {
                if (p > sqrt_candidate) {
                    break;
                }
                if (candidate % p == 0) {
                    is_prime = false;
                    break;
                }
            }

            if (is_prime) {
                primes.push_back(candidate);
            }
            candidate += 2;
        }

        return primes.back();
    }

}