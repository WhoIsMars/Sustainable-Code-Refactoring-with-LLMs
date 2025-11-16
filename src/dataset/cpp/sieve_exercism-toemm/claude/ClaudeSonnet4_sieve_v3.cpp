#include "sieve.h"

#include <vector>
#include <cmath>

namespace sieve {

std::vector<int> primes(int limit) {
    if (limit < 2) return {};
    
    std::vector<bool> marked(limit + 1, false);
    std::vector<int> result;
    result.reserve(static_cast<size_t>(limit / std::log(limit) * 1.25));
    
    if (limit >= 2) {
        result.push_back(2);
        for (int multiple = 4; multiple <= limit; multiple += 2) {
            marked[multiple] = true;
        }
    }
    
    const int sqrt_limit = static_cast<int>(std::sqrt(limit));
    
    for (int candidate = 3; candidate <= limit; candidate += 2) {
        if (marked[candidate]) continue;
        
        result.push_back(candidate);
        
        if (candidate <= sqrt_limit) {
            for (int multiple = candidate * candidate; multiple <= limit; multiple += candidate * 2) {
                marked[multiple] = true;
            }
        }
    }
    
    return result;
}

}  // namespace sieve