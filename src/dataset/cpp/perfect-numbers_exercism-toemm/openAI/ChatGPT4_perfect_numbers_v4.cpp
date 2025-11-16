#include "perfect_numbers.h"

#include <stdexcept>
#include <cmath>

namespace perfect_numbers {

classification classify(int num) {
    if (num <= 0) throw std::domain_error("Number invalid.");
    
    int sum = 1;
    int sqrt_num = static_cast<int>(std::sqrt(num));

    for (int i = 2; i <= sqrt_num; ++i) {
        if (num % i == 0) {
            sum += i;
            int pair = num / i;
            if (pair != i) sum += pair;
        }
    }

    if (num == 1) sum = 0; // Special case for 1
    if (num == sum) return classification::perfect;
    if (sum < num) return classification::deficient;
    return classification::abundant;
}

}  // namespace perfect_numbers