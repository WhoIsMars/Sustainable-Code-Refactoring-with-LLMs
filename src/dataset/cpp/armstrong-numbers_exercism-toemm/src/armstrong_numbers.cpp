#include "armstrong_numbers.h"

namespace armstrong_numbers {

bool is_armstrong_number(int num) {

    int exp = log10(num) + 1;
    int sum{};
    
    for (int q = num; q != 0; q /= 10) {

        sum += std::pow(q % 10, exp);
    }

    return sum == num;


}

}  // namespace armstrong_numbers
