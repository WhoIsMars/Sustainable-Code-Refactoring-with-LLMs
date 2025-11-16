#include "sieve.h"

#include <vector>
#include <cmath>

namespace sieve {

std::vector<int> primes(int limit) {
    if (limit < 2) return {};

    std::vector<bool> marked(limit + 1, true);
    marked[0] = marked[1] = false;

    int sqrt_limit = static_cast<int>(std::sqrt(limit));
    for (int candidate = 2; candidate <= sqrt_limit; ++candidate) {
        if (marked[candidate]) {
            for (int multiple = candidate * candidate; multiple <= limit; multiple += candidate) {
                marked[multiple] = false;
            }
        }
    }

    std::vector<int> primes;
    primes.reserve(limit / std::log(limit)); // Approximation for the number of primes
    for (int i = 2; i <= limit; ++i) {
        if (marked[i]) primes.push_back(i);
    }

    return primes;
}

}  // namespace sieve