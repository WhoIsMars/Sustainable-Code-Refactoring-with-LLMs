#include "prime_factors.h"

namespace prime_factors
{
    vector<int> of(int n)
    {
        vector<int> result;
        if (n <= 1) return result;
        
        result.reserve(32); // Reserve space to avoid reallocations
        
        // Handle factor 2 separately
        while (n % 2 == 0) {
            result.push_back(2);
            n /= 2;
        }
        
        // Check odd factors up to sqrt(n)
        for (int i = 3; i * i <= n; i += 2) {
            while (n % i == 0) {
                result.push_back(i);
                n /= i;
            }
        }
        
        // If n is still > 1, then it's a prime
        if (n > 1) {
            result.push_back(n);
        }
        
        return result;
    }
    
    void factor(int n, vector<int> &result)
    {
        if (n <= 1) return;
        
        // Handle factor 2 separately
        while (n % 2 == 0) {
            result.push_back(2);
            n /= 2;
        }
        
        // Check odd factors up to sqrt(n)
        for (int i = 3; i * i <= n; i += 2) {
            while (n % i == 0) {
                result.push_back(i);
                n /= i;
            }
        }
        
        // If n is still > 1, then it's a prime
        if (n > 1) {
            result.push_back(n);
        }
    }
} // namespace prime_factors