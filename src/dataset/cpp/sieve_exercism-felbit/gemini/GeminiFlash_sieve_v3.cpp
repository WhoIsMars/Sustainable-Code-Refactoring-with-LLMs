#include "sieve.h"
#include <cmath>
#include <numeric>
#include <vector>

namespace sieve {
    auto primes(int n) -> const std::vector<int>
    {
        if (n < 2) {
            return {};
        }

        std::vector<bool> is_prime(n + 1, true);
        std::vector<int> prime_numbers;

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
                prime_numbers.push_back(p);
            }
        }

        return prime_numbers;
    }
}