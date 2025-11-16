#include "nth_prime.h"

#include <stdexcept>
#include <cmath>

namespace nth_prime {

bool is_prime(int i) {
    if (i < 2) return false;
    if (i == 2 || i == 3) return true;
    if (i % 2 == 0 || i % 3 == 0) return false;
    for (int j = 5; j <= std::sqrt(i); j += 6) {
        if (i % j == 0 || i % (j + 2) == 0) return false;
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