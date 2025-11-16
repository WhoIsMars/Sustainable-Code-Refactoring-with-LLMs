#include "perfect_numbers.h"

#include <stdexcept>

namespace perfect_numbers {

classification classify(int num) {
  if (num <= 0) {
    throw std::domain_error("Number invalid.");
  }

  int sum = 1; 

  if (num > 1) {
    for (int i = 2; i * i <= num; ++i) {
      if (num % i == 0) {
        sum += i;
        if (i * i != num) {
          sum += num / i;
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