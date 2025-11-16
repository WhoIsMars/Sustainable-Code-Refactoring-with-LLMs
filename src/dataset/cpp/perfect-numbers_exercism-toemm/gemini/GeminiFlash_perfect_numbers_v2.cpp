#include "perfect_numbers.h"

#include <stdexcept>
#include <cmath>

namespace perfect_numbers {

classification classify(int num) {
    if (num <= 0) {
        throw std::domain_error("Number invalid.");
    }

    int sum = 1; // Initialize sum with 1, as 1 is always a divisor

    if (num == 1) return classification::deficient; //Early return for 1

    for (int i = 2; i <= std::sqrt(num); ++i) {
        if (num % i == 0) {
            sum += i;
            if (i * i != num) { // Avoid adding the same factor twice for perfect squares
                sum += num / i;
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