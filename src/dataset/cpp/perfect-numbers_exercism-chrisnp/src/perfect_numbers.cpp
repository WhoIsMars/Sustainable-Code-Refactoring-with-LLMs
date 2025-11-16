#include "perfect_numbers.h"
#include <stdexcept>
#include <cmath>

namespace perfect_numbers {

classification classify(int n) {
    if (n <= 0) throw std::domain_error("Natural numbers only");
    int aliquot{n == 1 ? 0 : 1},
        lim{static_cast<int>(std::sqrt(n))};
    for (int f{2}; f <= lim; ++f) if (n % f == 0) {
        aliquot += f;
        if ((n / f) != f) aliquot += n / f;
    }
    if (aliquot < n)
        return deficient;
    if (aliquot > n) 
        return abundant;
    return perfect;
}
}  // namespace perfect_numbers
