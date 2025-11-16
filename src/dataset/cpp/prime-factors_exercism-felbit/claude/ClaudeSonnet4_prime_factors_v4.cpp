#include "prime_factors.h"

namespace prime_factors
{
    std::vector<int> of(int n)
    {
        if (n < 2) return {};

        std::vector<int> result;
        result.reserve(32);

        while (n % 2 == 0) {
            result.push_back(2);
            n /= 2;
        }

        for (int m = 3; m * m <= n; m += 2) {
            while (n % m == 0) {
                result.push_back(m);
                n /= m;
            }
        }

        if (n > 2) {
            result.push_back(n);
        }

        return result;
    }
}