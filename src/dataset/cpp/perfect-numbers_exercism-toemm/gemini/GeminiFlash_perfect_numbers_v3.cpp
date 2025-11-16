#include "perfect_numbers.h"

#include <stdexcept>
#include <cmath>

namespace perfect_numbers {

classification classify(int num) {
    if (num <= 0) {
        throw std::domain_error("Number invalid.");
    }

    int sum = 1; 

    if (num > 1) {
        for (int i = 2; i <= std::sqrt(num); ++i) {
            if (num % i == 0) {
                sum += i;
                int divisor = num / i;
                if (divisor != i) {
                    sum += divisor;
                }
            }
        }
    }

    if (num == sum) {
        return classification::perfect;
    } else if (sum < num) {
        return classification::deficient;
    } else {
        return classification::abundant;
    }
}

}  // namespace perfect_numbers