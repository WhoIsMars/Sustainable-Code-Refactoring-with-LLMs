#include "prime_factors.h"

namespace prime_factors
{
    vector<int> of(int n)
    {
        vector<int> result;
        if (n <= 1) return result;
        
        result.reserve(32);
        
        while (n % 2 == 0) {
            result.push_back(2);
            n /= 2;
        }
        
        for (int i = 3; i * i <= n; i += 2) {
            while (n % i == 0) {
                result.push_back(i);
                n /= i;
            }
        }
        
        if (n > 2) {
            result.push_back(n);
        }
        
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
}