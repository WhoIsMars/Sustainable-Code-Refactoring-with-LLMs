#include "perfect_numbers.h"
#include <stdexcept>
#include <cmath>

namespace perfect_numbers {

classification classify(int n) {
    if (n <= 0) throw std::domain_error("Natural numbers only");
    if (n == 1) return deficient;

    int aliquot = 1;
    int lim = static_cast<int>(std::sqrt(n));
    for (int f = 2; f <= lim; ++f) {
        if (n % f == 0) {
            aliquot += f;
            int pair = n / f;
            if (pair != f) aliquot += pair;
            if (aliquot > n) return abundant; // Early exit for efficiency
        }
    }
    return (aliquot == n) ? perfect : deficient;
}

}  // namespace perfect_numbers