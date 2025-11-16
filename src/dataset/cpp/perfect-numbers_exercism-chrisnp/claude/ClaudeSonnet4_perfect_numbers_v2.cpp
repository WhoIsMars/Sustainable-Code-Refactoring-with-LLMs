#include "perfect_numbers.h"
#include <stdexcept>

namespace perfect_numbers {

classification classify(int n) {
    if (n <= 0) throw std::domain_error("Natural numbers only");
    
    if (n == 1) return deficient;
    
    int aliquot = 1;
    int f = 2;
    
    while (f * f <= n) {
        if (n % f == 0) {
            aliquot += f;
            int quotient = n / f;
            if (quotient != f) {
                aliquot += quotient;
                if (aliquot > n) return abundant;
            }
        }
        ++f;
    }
    
    if (aliquot < n) return deficient;
    if (aliquot > n) return abundant;
    return perfect;
}

}  // namespace perfect_numbers