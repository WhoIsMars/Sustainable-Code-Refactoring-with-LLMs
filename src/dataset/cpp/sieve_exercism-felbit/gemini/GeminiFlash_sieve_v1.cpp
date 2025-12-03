#include "sieve.h"
#include <vector>
#include <numeric>
#include <cmath>

namespace sieve {
    auto primes(int n) -> const std::vector<int>
    {
        if (n < 2) {
            return {};
        }

        std::vector<bool> is_prime(n + 1, true);
        std::vector<int> primes_list;

        is_prime[0] = is_prime[1] = false;

        for (int p = 2; p * p <= n; ++p) {
            if (is_prime[p]) {
                for (int i = p * p; i <= n; i += p) {
                    is_prime[i] = false;
                }
            }
        }

        for (int p = 2; p <= n; ++p) {
            if (is_prime[p]) {
                primes_list.push_back(p);
            }
        }

        return primes_list;
    }
}