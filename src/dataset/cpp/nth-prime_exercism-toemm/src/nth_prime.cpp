#include "nth_prime.h"

#include <stdexcept>

namespace nth_prime {

bool is_prime(int i) {

    if (i==2) return true;
    
    for (int j{2}; j < i; j++) {
        if (i % j == 0) return false;
    }
    return true;

}

int nth(int i) {

    if (i <= 0) throw std::domain_error("invalid i");
    int prime_ctr{};
    int nr{2};

    while (prime_ctr < i) {

        if (is_prime(nr)) prime_ctr++;
        nr++;

    }
    
    return --nr;

}





}  // namespace nth_prime
