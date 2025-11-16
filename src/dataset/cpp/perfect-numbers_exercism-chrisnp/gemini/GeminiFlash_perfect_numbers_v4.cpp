#include "perfect_numbers.h"
#include <stdexcept>
#include <cmath>

namespace perfect_numbers {

classification classify(int n) {
    if (n <= 0) {
        throw std::domain_error("Natural numbers only");
    }

    if (n == 1) {
        return deficient;
    }

    int aliquot_sum = 1;
    int limit = static_cast<int>(std::sqrt(n));

    for (int i = 2; i <= limit; ++i) {
        if (n % i == 0) {
            aliquot_sum += i;
            int divisor = n / i;
            if (divisor != i) {
                aliquot_sum += divisor;
            }
        }
    }

    if (aliquot_sum < n) {
        return deficient;
    } else if (aliquot_sum > n) {
        return abundant;
    } else {
        return perfect;
    }
}

}  // namespace perfect_numbers