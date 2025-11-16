#include "perfect_numbers.h"
#include <stdexcept>
#include <cmath>

namespace perfect_numbers {

classification classify(int number) {
    if (number <= 0) {
        throw std::domain_error("Natural numbers only");
    }

    if (number == 1) {
        return deficient;
    }

    int aliquot_sum = 1;
    int limit = static_cast<int>(std::sqrt(number));

    for (int factor = 2; factor <= limit; ++factor) {
        if (number % factor == 0) {
            aliquot_sum += factor;
            int other_factor = number / factor;
            if (other_factor != factor) {
                aliquot_sum += other_factor;
            }
        }
    }

    if (aliquot_sum < number) {
        return deficient;
    } else if (aliquot_sum > number) {
        return abundant;
    } else {
        return perfect;
    }
}

}  // namespace perfect_numbers