#include "perfect_numbers.h"
#include <stdexcept>

namespace perfect_numbers {

classification classify(int n) {
    if (n <= 0) throw std::domain_error("Natural numbers only");
    
    if (n == 1) return deficient;
    
    int aliquot = 1;
    
    for (int f = 2; f * f <= n; ++f) {
        if (n % f == 0) {
            aliquot += f;
            int quotient = n / f;
            if (quotient != f) {
                aliquot += quotient;
            }
            if (aliquot > n) return abundant;
        }
    }
    
    return (aliquot == n) ? perfect : deficient;
}

}  // namespace perfect_numbers