#include "sieve.h"
#include <cmath>

namespace sieve {
    auto primes(int n) -> const std::vector<int>
    {
        if (n < 2) {
            return {};
        }

        std::vector<bool> is_prime(n, true);
        std::vector<int> primes_list;

        is_prime[0] = false;

        for (int p = 2; p * p <= n; ++p) {
            if (is_prime[p - 1]) {
                for (int i = p * p; i <= n; i += p) {
                    is_prime[i - 1] = false;
                }
            }
        }

        for (int p = 2; p <= n; ++p) {
            if (is_prime[p - 1]) {
                primes_list.push_back(p);
            }
        }

        return primes_list;
    }
}