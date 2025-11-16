#include "prime_factors.h"

#include <vector>
#include <cmath>

namespace prime_factors {

using namespace std;


vector<long long> of(long long n) {

    vector<long long> factors;

    if (n <= 1) {
        return factors;
    }

    while (n % 2 == 0) {
        factors.push_back(2);
        n /= 2;
    }

    for (long long i = 3; i <= sqrt(n); i += 2) {
        while (n % i == 0) {
            factors.push_back(i);
            n /= i;
        }
    }

    if (n > 2) {
        factors.push_back(n);
    }

    return factors;

}


}  // namespace prime_factors