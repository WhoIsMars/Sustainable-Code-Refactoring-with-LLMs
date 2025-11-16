#include "nth_prime.h"

#include <stdexcept>
#include <cmath>

namespace nth_prime {

bool is_prime(int n) {
    if (n < 2) return false;
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (int i = 5; i <= std::sqrt(n); i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

int nth(int i) {
    if (i <= 0) throw std::domain_error("invalid i");
    int prime_ctr = 0;
    int nr = 1;

    while (prime_ctr < i) {
        nr++;
        if (is_prime(nr)) prime_ctr++;
    }

    return nr;
}

}  // namespace nth_prime