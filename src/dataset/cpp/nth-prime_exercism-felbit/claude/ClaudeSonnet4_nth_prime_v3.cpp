#include "nth_prime.h"
#include <cmath>

namespace prime {

    int nth(unsigned long n)
    {
        if (n < 1) throw std::domain_error("Non positive number given!");
        
        if (n == 1) return 2;
        
        std::vector<int> primes;
        primes.reserve(n);
        primes.push_back(2);
        
        int candidate = 3;
        
        while (primes.size() < n) {
            bool is_prime = true;
            int sqrt_candidate = static_cast<int>(std::sqrt(candidate));
            
            for (int prime : primes) {
                if (prime > sqrt_candidate) break;
                if (candidate % prime == 0) {
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