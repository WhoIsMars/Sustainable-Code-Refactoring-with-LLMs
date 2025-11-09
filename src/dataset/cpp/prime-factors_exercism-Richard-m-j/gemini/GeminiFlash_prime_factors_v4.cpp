#include "prime_factors.h"
#include <cmath>

namespace prime_factors
{
    vector<int> of(int n)
    {
        vector<int> result;
        int num = n;
        for (int i = 2; i <= sqrt(num); ++i)
        {
            while (num % i == 0)
            {
                result.push_back(i);
                num /= i;
            }
        }
        if (num > 1)
        {
            result.push_back(num);
        }
        return result;
    }
} // namespace prime_factors