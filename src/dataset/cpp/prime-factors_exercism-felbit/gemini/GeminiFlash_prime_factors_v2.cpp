#include "prime_factors.h"
#include <cmath>

namespace prime_factors
{
    std::vector<int> of(int n)
    {
        std::vector<int> result {};
        if (n < 2) return result;

        while (n % 2 == 0) {
            result.push_back(2);
            n /= 2;
        }

        for (int i = 3; i <= std::sqrt(n); i += 2) {
            while (n % i == 0) {
                result.push_back(i);
                n /= i;
            }
        }

        if (n > 1) {
            result.push_back(n);
        }

        return result;
    }
}