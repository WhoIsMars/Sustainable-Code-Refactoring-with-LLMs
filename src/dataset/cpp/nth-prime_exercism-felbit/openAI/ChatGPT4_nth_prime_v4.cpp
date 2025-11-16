#include "nth_prime.h"
#include <cmath>
#include <vector>

namespace prime {

    int nth(unsigned long n)
    {
        if (n < 1) throw std::domain_error("Non positive number given!");

        std::vector<int> primes;
        primes.reserve(n);
        primes.push_back(2);

        int candidate = 3;

        while (primes.size() < n)
        {
            bool is_prime = true;
            int limit = static_cast<int>(std::sqrt(candidate));
            for (int p : primes)
            {
                if (p > limit) break;
                if (candidate % p == 0)
                {
                    is_prime = false;
                    break;
                }
            }

            if (is_prime) primes.push_back(candidate);
            candidate += 2;
        }

        return primes.back();
    }

}