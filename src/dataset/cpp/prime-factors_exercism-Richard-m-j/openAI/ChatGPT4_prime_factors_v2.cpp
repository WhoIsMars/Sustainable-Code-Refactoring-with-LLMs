#include "prime_factors.h"

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
        for (int i = 2; i * i <= n; ++i)
        {
            while (n % i == 0)
            {
                result.push_back(i);
                n /= i;
            }
        }
        if (n > 1)
        {
            result.push_back(n);
        }
    }
} // namespace prime_factors