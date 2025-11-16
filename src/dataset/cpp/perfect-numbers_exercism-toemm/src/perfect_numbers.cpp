#include "perfect_numbers.h"

#include <stdexcept>

namespace perfect_numbers {



classification classify(int num) {


    if (num <= 0) throw std::domain_error("Number invalid.");
    
    int sum{};

    for (int i{1}; i <= num/2; i++) {

        // find factors
        if (num % i == 0) sum += i;

    }

    if (num == sum) return classification::perfect;
    else if (sum < num) return classification::deficient;
    else return classification::abundant;


}




}  // namespace perfect_numbers
