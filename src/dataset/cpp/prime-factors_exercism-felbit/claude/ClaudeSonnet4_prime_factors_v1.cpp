#include "prime_factors.h"

namespace prime_factors
{
    std::vector<int> of(int n)
    {
        std::vector<int> result;
        if (n < 2) return result;

        // Handle factor 2 separately
        while (n % 2 == 0) {
            result.push_back(2);
            n /= 2;
        }

        // Check odd factors starting from 3
        for (int m = 3; m * m <= n; m += 2) {
            while (n % m == 0) {
                result.push_back(m);
                n /= m;
            }
        }

        // If n is still greater than 1, it's a prime factor
        if (n > 1) {
            result.push_back(n);
        }

        return result;
    }
}