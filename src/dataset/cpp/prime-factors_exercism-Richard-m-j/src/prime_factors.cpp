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
        int i;
        for (i = 2; i < n; i++)
            if (n % i == 0)
            {
                result.push_back(i);
                factor(n / i, result);
                break;
            }
        if (i == n)
            result.push_back(n);
    }
} // namespace prime_factors
