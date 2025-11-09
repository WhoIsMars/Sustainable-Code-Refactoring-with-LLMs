#include "prime_factors.h"
#include <cmath>

namespace prime_factors
{
    vector<int> of(int n)
    {
        vector<int> result;
        factor(n, result);
        return result;
    }

    void factor(int n, vector<int> &result)
    {
        while (n % 2 == 0)
        {
            result.push_back(2);
            n /= 2;
        }

        for (int i = 3; i <= std::sqrt(n); i += 2)
        {
            while (n % i == 0)
            {
                result.push_back(i);
                n /= i;
            }
        }

        if (n > 2)
        {
            result.push_back(n);
        }
    }
} // namespace prime_factors