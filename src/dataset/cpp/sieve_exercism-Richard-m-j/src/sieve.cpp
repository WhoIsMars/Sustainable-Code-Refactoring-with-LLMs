#include "sieve.h"

namespace sieve
{
    vector<int> primes(int limit)
    {
        vector<bool> isprime(limit, true);
        for (int i = 2; i <= limit; i++)
            if (isprime[i])
                for (int j = i; i * j <= limit; j++)
                    isprime[i * j] = false;

        vector<int> primes;
        for (int i = 2; i <= limit; i++)
            if (isprime[i])
                primes.push_back(i);

        return primes;
    }
} // namespace sieve
