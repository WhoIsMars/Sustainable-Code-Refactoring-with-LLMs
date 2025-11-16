#include "sieve.h"

#include <vector>
#include <cmath>

namespace sieve {

std::vector<int> primes(int limit) {
    if (limit < 2) {
        return {};
    }

    std::vector<bool> is_prime(limit + 1, true);
    std::vector<int> primes_list;

    is_prime[0] = is_prime[1] = false;

    for (int p = 2; p * p <= limit; ++p) {
        if (is_prime[p]) {
            for (int i = p * p; i <= limit; i += p) {
                is_prime[i] = false;
            }
        }
    }

    for (int p = 2; p <= limit; ++p) {
        if (is_prime[p]) {
            primes_list.push_back(p);
        }
    }

    return primes_list;
}

}  // namespace sieve