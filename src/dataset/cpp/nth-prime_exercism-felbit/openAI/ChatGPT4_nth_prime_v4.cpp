#include "nth_prime.h"
#include <vector>
#include <cmath>

namespace prime {

    int nth(unsigned long n)
    {
        if (n < 1) throw std::domain_error("Non positive number given!");

        std::vector<int> primes;
        primes.reserve(n); // Reserve memory to avoid frequent reallocations
        primes.push_back(2); // Start with the first prime number

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

            candidate += 2; // Skip even numbers
        }

        return primes.back();
    }

}