#include "sieve.h"

#include <vector>
#include <bitset>

namespace sieve {

std::vector<int> primes(int limit) {
    if (limit < 2) return {};
    
    std::vector<bool> is_prime(limit + 1, true);
    is_prime[0] = is_prime[1] = false;
    
    std::vector<int> result;
    result.reserve(limit / (std::log(limit) * 0.9));
    
    for (int i = 2; i * i <= limit; ++i) {
        if (is_prime[i]) {
            for (int j = i * i; j <= limit; j += i) {
                is_prime[j] = false;
            }
        }
    }
    
    for (int i = 2; i <= limit; ++i) {
        if (is_prime[i]) {
            result.push_back(i);
        }
    }
    
    return result;
}

}  // namespace sieve