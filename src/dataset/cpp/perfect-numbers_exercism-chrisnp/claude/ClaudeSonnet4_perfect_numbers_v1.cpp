#include "perfect_numbers.h"
#include <stdexcept>

namespace perfect_numbers {

classification classify(int n) {
    if (n <= 0) throw std::domain_error("Natural numbers only");
    
    if (n == 1) return deficient;
    
    int aliquot = 1;
    int i = 2;
    
    while (i * i <= n) {
        if (n % i == 0) {
            aliquot += i;
            int quotient = n / i;
            if (quotient != i) {
                aliquot += quotient;
            }
            if (aliquot > n) return abundant;
        }
        ++i;
    }
    
    return (aliquot == n) ? perfect : deficient;
}

}  // namespace perfect_numbers