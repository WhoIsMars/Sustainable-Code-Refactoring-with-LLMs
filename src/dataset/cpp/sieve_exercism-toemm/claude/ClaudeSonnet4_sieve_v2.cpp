#include "sieve.h"

#include <vector>
#include <bitset>

namespace sieve {

std::vector<int> primes(int limit) {
    if (limit < 2) return {};
    
    std::vector<bool> marked(limit + 1, false);
    std::vector<int> primes{};
    primes.reserve(limit / (std::log(limit) - 1)); // Approximate prime count
    
    // Handle 2 separately to allow odd-only optimization
    primes.push_back(2);
    
    // Mark all even numbers as composite
    for (int i = 4; i <= limit; i += 2) {
        marked[i] = true;
    }
    
    // Only check odd numbers starting from 3
    for (int candidate = 3; candidate <= limit; candidate += 2) {
        if (marked[candidate]) continue;
        
        primes.push_back(candidate);
        
        // Start from candidate^2 and increment by 2*candidate to stay odd
        for (long long multiple = (long long)candidate * candidate; 
             multiple <= limit; 
             multiple += 2LL * candidate) {
            marked[multiple] = true;
        }
    }
    
    return primes;
}

}  // namespace sieve