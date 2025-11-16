#include "sieve.h"

namespace sieve {
    auto primes(int n) -> const std::vector<int>
    {
        if (n < 2) return {};
        
        std::vector<bool> is_prime(n + 1, true);
        std::vector<int> result;
        
        is_prime[0] = is_prime[1] = false;
        
        for (int i = 2; i * i <= n; ++i) {
            if (is_prime[i]) {
                for (int j = i * i; j <= n; j += i) {
                    is_prime[j] = false;
                }
            }
        }
        
        result.reserve(n / (std::log(n) > 0 ? std::log(n) : 1));
        
        for (int i = 2; i <= n; ++i) {
            if (is_prime[i]) {
                result.push_back(i);
            }
        }
        
        return result;
    }
}