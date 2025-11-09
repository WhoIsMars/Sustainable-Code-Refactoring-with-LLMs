#include "prime_factors.h"
#include <cmath>

namespace prime_factors
{
    vector<int> of(int n)
    {
        vector<int> result;
        int divisor = 2;
        while (n > 1 && divisor <= sqrt(n))
        {
            if (n % divisor == 0)
            {
                result.push_back(divisor);
                n /= divisor;
            }
            else
            {
                divisor++;
            }
        }
        if (n > 1)
        {
            result.push_back(n);
        }
        return result;
    }
} // namespace prime_factors