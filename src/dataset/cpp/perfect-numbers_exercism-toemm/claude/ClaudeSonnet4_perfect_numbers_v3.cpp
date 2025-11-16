#include "perfect_numbers.h"

#include <stdexcept>
#include <cmath>

namespace perfect_numbers {

classification classify(int num) {
    if (num <= 0) throw std::domain_error("Number invalid.");
    
    if (num == 1) return classification::deficient;
    
    int sum = 1;
    int sqrt_num = static_cast<int>(std::sqrt(num));
    
    for (int i = 2; i <= sqrt_num; ++i) {
        if (num % i == 0) {
            sum += i;
            if (i != num / i) {
                sum += num / i;
            }
        }
    }
    
    if (num == sum) return classification::perfect;
    else if (sum < num) return classification::deficient;
    else return classification::abundant;
}

}  // namespace perfect_numbers